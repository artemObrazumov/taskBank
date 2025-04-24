#include "controlworkpdfexporter.h"
#include "models/controlwork.h"
#include <iostream>
#include <sstream>
#include <fstream>

ControlWorkPdfExporter::ControlWorkPdfExporter(ControlWork work) {
    this->outputPath = work.path + "/" + work.title;
}

std::vector<std::string> process_text(HPDF_Page page, const std::string& text,
                                      float max_width, HPDF_Font font, float font_size) {
    std::vector<std::string> result;
    std::istringstream iss(text);
    std::string paragraph;
    HPDF_Page_SetFontAndSize(page, font, font_size);

    while (std::getline(iss, paragraph)) {
        if (paragraph.empty()) {
            result.push_back("");
            continue;
        }
        std::istringstream word_stream(paragraph);
        std::string word;
        std::string current_line;

        while (word_stream >> word) {
            std::string test_line = current_line.empty() ? word : current_line + " " + word;
            float width = HPDF_Page_TextWidth(page, test_line.c_str());
            if (width <= max_width || current_line.empty()) {
                current_line = test_line;
            } else {
                result.push_back(current_line);
                current_line = word;
            }
        }

        if (!current_line.empty()) {
            result.push_back(current_line);
        }
    }

    return result;
}

void draw_advanced_text(HPDF_Doc pdf, HPDF_Page &page, HPDF_Font font,
                        float x, float &y, const std::string& text, float line_height, float font_size = 14) {
    float max_width = HPDF_Page_GetWidth(page) - 2 * x;
    auto lines = process_text(page, text, max_width, font, font_size);
    HPDF_Page_SetFontAndSize(page, font, font_size);

    for (const auto& line : lines) {
        if (line.empty()) {
            y -= line_height;
            continue;
        }

        if (y < 50) {
            page = HPDF_AddPage(pdf);
            HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
            HPDF_Page_SetFontAndSize(page, font, font_size);
            y = HPDF_Page_GetHeight(page) - 50;
        }

        HPDF_Page_BeginText(page);
        HPDF_Page_MoveTextPos(page, x, y);
        HPDF_Page_ShowText(page, line.c_str());
        HPDF_Page_EndText(page);
        y -= line_height;
    }
}

void printTitle(HPDF_Page page, std::string title, float &y, float line_height) {
    float x;
    float pageWidth = HPDF_Page_GetWidth(page);

    std::string workText = "Работа по теме:";
    float workTextWidth = HPDF_Page_TextWidth(page, workText.c_str());
    x = (pageWidth - workTextWidth) / 2;
    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, x, y);
    HPDF_Page_ShowText(page, workText.c_str());
    HPDF_Page_EndText(page);

    y -= line_height;

    std::string formattedTitle = "«" + title + "»";
    float titleWidth = HPDF_Page_TextWidth(page, formattedTitle.c_str());
    x = (pageWidth - titleWidth) / 2;
    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, x, y);
    HPDF_Page_ShowText(page, formattedTitle.c_str());
    HPDF_Page_EndText(page);

    y -= line_height;
}

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data) {
    std::cerr << "PDF Error: " << error_no << " (Detail: " << detail_no << ")" << std::endl;
}

void printTask(HPDF_Doc pdf, HPDF_Page page, HPDF_Font font, TaskGroup group, float &y, float line_height, const float x = 50) {
    std::string task_header = "Задание №" + std::to_string(group.index);
    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, x, y);
    HPDF_Page_ShowText(page, task_header.c_str());
    HPDF_Page_EndText(page);
    y -= line_height;
    draw_advanced_text(pdf, page, font, x, y, group.tasks[0].content, line_height);
    y -= line_height;
}

void printAnswer(HPDF_Doc pdf, HPDF_Page page, HPDF_Font font, TaskGroup group, float &y, float line_height, const float x = 50) {
    std::string task_header = "Задание №" + std::to_string(group.index);
    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, x, y);
    HPDF_Page_ShowText(page, task_header.c_str());
    HPDF_Page_EndText(page);
    y -= line_height;
    draw_advanced_text(pdf, page, font, x, y, "Ответ: " + group.tasks[0].answer, line_height);
    y -= line_height;
}

int ControlWorkPdfExporter::exportVariant(int id, std::vector<TaskGroup> groups, std::string title) {
    HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

    const int margin = 50;
    float line_height = 20;

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    float y = HPDF_Page_GetHeight(page) - margin;

    const char* font_name = HPDF_LoadTTFontFromFile(pdf, "tnr.ttf", HPDF_TRUE);
    HPDF_UseUTFEncodings(pdf);
    HPDF_Font font = HPDF_GetFont(pdf, font_name, "UTF-8");
    HPDF_Page_SetFontAndSize(page, font, 18);

    printTitle(page, title, y, line_height);

    y -= 20;
    HPDF_Page_SetFontAndSize(page, font, 14);
    line_height = 16;

    for (const auto& group : groups) {
        printTask(pdf, page, font, group, y, line_height, margin);
    }

    std::string variantsPath = this->outputPath + "/variants/";
    std::filesystem::create_directory(variantsPath);

    std::string path = variantsPath + std::to_string(id) + ".pdf";
    HPDF_SaveToFile(pdf, path.c_str());
    HPDF_Free(pdf);
    return 0;
}

int ControlWorkPdfExporter::exportAnswers(int id, std::vector<TaskGroup> groups, std::string title) {
    HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

    const int margin = 50;
    float line_height = 20;

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    float y = HPDF_Page_GetHeight(page) - margin;

    const char* font_name = HPDF_LoadTTFontFromFile(pdf, "tnr.ttf", HPDF_TRUE);
    HPDF_UseUTFEncodings(pdf);
    HPDF_Font font = HPDF_GetFont(pdf, font_name, "UTF-8");
    HPDF_Page_SetFontAndSize(page, font, 18);

    printTitle(page, title, y, line_height);

    y -= 20;
    HPDF_Page_SetFontAndSize(page, font, 14);
    line_height = 16;

    for (const auto& group : groups) {
        printAnswer(pdf, page, font, group, y, line_height, margin);
    }

    std::string answersPath = this->outputPath + "/answers/";
    std::filesystem::create_directory(answersPath);

    std::string path = answersPath + std::to_string(id) + ".pdf";
    HPDF_SaveToFile(pdf, path.c_str());
    HPDF_Free(pdf);
    return 0;
}
