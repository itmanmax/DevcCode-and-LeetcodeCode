#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <zip.h>

#define FILENAME "C:test题库.docx"
#define MAX_QUESTIONS 100

typedef struct {
    char question[256];
    char options[4][256];
} Question;

Question questions[MAX_QUESTIONS];
int total_questions = 0;

void read_questions_from_docx(const char *filename);
void select_random_questions(int count);
void show_selected_questions(int count);

static void on_button_clicked(GtkWidget *widget, gpointer data) {
    int count = GPOINTER_TO_INT(data);
    select_random_questions(count);
    show_selected_questions(count);
}

void read_questions_from_docx(const char *filename) {
    // 解压并读取.docx文件中的题目
    struct zip *archive = zip_open(filename, 0, NULL);
    if (!archive) {
        fprintf(stderr, "Failed to open docx file\n");
        return;
    }
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(archive, "word/document.xml", 0, &st);
    struct zip_file *file = zip_fopen(archive, "word/document.xml", 0);
    char *contents = malloc(st.size);
    zip_fread(file, contents, st.size);
    zip_fclose(file);
    zip_close(archive);

    xmlDoc *doc = xmlReadMemory(contents, st.size, "document.xml", NULL, 0);
    if (!doc) {
        fprintf(stderr, "Failed to parse XML\n");
        return;
    }
    xmlNode *root = xmlDocGetRootElement(doc);
    xmlNode *body = root->children;

    total_questions = 0;
    int option_index = 0;
    xmlNode *cur = body->children;
    while (cur && total_questions < MAX_QUESTIONS) {
        if (!xmlStrcmp(cur->name, (const xmlChar *)"p")) {
            xmlChar *content = xmlNodeGetContent(cur);
            if (option_index == 0) {
                strncpy(questions[total_questions].question, (const char *)content, 255);
            } else {
                strncpy(questions[total_questions].options[option_index - 1], (const char *)content, 255);
            }
            xmlFree(content);
            option_index++;
            if (option_index == 5) {
                option_index = 0;
                total_questions++;
            }
        }
        cur = cur->next;
    }
    xmlFreeDoc(doc);
    free(contents);
}

void select_random_questions(int count) {
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int index = rand() % total_questions;
        Question temp = questions[i];
        questions[i] = questions[index];
        questions[index] = temp;
    }
}

void show_selected_questions(int count) {
    for (int i = 0; i < count; i++) {
        printf("Question %d: %s\n", i + 1, questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("Option %c: %s\n", 'A' + j, questions[i].options[j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Random Question Selector");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *label = gtk_label_new("Enter number of questions:");
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);

    GtkWidget *button = gtk_button_new_with_label("Submit");
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);

    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), (gpointer)atoi(gtk_entry_get_text(GTK_ENTRY(entry))));

    read_questions_from_docx(FILENAME);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

