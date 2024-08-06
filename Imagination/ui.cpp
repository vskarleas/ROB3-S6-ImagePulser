// #############################################################################
// # File ui.c
// # Project in C - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Evinia Anastasopoulou, Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

/**
 * @file ui.cpp
 * @brief L'interface graphique
 *
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function prototypes
void segments_clicked(GtkWidget *pButton, gpointer data);
void bezier2_clicked(GtkWidget *pButton, gpointer data);
void bezier3_clicked(GtkWidget *pButton, gpointer data);
void cartoonize_clicked(GtkWidget *pButton, gpointer data);
void show_image_found_options(GtkWidget *pVBox);
void show_no_image_found_options(GtkWidget *pVBox);
void show_default_page(GtkWidget *pVBox);
void check_image_and_update_ui(GtkWidget *pVBox);
void image_capture_clicked(GtkWidget *pButton, gpointer data);
void show_input_dialog(GtkWidget *pWidget, gpointer data);
void execute_command_and_display_output(const char *command, GtkWidget *pVBox);

// Structure to hold method information
typedef struct
{
    GtkWidget *pVBox;
    const char *method;
} MethodData;

// Function to check the first character of a file
gboolean tmp_image_found(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return FALSE; // File couldn't be opened
    }

    int ch = fgetc(file);
    fclose(file);

    if (ch == '1')
    {
        return TRUE; // First character is '1'
    }

    return FALSE; // First character is not '1'
}

// Function to execute command and display output in a GTK widget
void execute_command_and_display_output(const char *command, GtkWidget *pVBox)
{
    FILE *fp;
    char buffer[1024];
    GString *output = g_string_new("");

    // Open the command for reading
    fp = popen(command, "r");
    if (fp == NULL)
    {
        g_print("Failed to run command\n");
        return;
    }

    // Read the output a line at a time
    while (fgets(buffer, sizeof(buffer) - 1, fp) != NULL)
    {
        g_string_append(output, buffer);
    }

    // Close the command
    pclose(fp);

    // Create a label for the "Console:" text
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>Console:</b>");

    // Create a text view to display the command output
    GtkWidget *text_view = gtk_text_view_new();
    GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(text_buffer, output->str, -1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE); // Make the text view read-only

    // Create a scrolled window and add the text view to it
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // Set the scrolled window to have minimum dimensions
    gtk_widget_set_size_request(scrolled_window, 480, 200);

    // Add the label and scrolled window to the pVBox
    gtk_box_pack_start(GTK_BOX(pVBox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), scrolled_window, TRUE, TRUE, 0);
    gtk_widget_show_all(pVBox);

    g_string_free(output, TRUE);
}

// Signal handler function that triggers the "Send" action when the "Enter" key is pressed
static void on_entry_activate(GtkEntry *entry, GtkDialog *dialog) {
    gtk_dialog_response(dialog, GTK_RESPONSE_ACCEPT);
}

// Function to show input dialog
void show_input_dialog(GtkWidget *pWidget, gpointer data)
{
    MethodData *methodData = (MethodData *)data;

    GtkWidget *dialog, *content_area, *entry, *label;
    GtkDialogFlags flags = (GtkDialogFlags)(GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT);

    dialog = gtk_dialog_new_with_buttons("Seuil Distance",
                                         GTK_WINDOW(gtk_widget_get_toplevel(methodData->pVBox)),
                                         flags,
                                         "Send",
                                         GTK_RESPONSE_ACCEPT,
                                         "Close",
                                         GTK_RESPONSE_REJECT,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    label = gtk_label_new("Please enter a positive integer:");
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter a positive number");

    // Connect the "activate" signal to the handler
    g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(on_entry_activate), dialog);

    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_add(GTK_CONTAINER(content_area), entry);

    gtk_widget_show_all(dialog);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT)
    {
        const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
        float d = atof(entry_text);

        if (d > 0)
        {
            char command[256];
            snprintf(command, sizeof(command), "./%s_simplification %f", methodData->method, d);
            g_print("Console: %s was called with d = %f\n", methodData->method, d);
            execute_command_and_display_output(command, methodData->pVBox);
        }
        else
        {
            GtkWidget *error_dialog;
            error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_CLOSE,
                                                  "Invalid input! Please enter a positive integer.");
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
        }
    }

    gtk_widget_destroy(dialog);
    free(methodData);
}

// Function callback executed when the "Segments" button is clicked
void segments_clicked(GtkWidget *pButton, gpointer data)
{
    // Process captured image to be saved on PBM format (codec P4)
    system("./image_processing");

    // Simplification data attribution (seuil as input)
    MethodData *methodData = (MethodData *)malloc(sizeof(MethodData));
    methodData->pVBox = GTK_WIDGET(data);
    methodData->method = "segments";
    show_input_dialog(pButton, methodData);
}

// Function callback executed when the "Bezier ordre 2" button is clicked
void bezier2_clicked(GtkWidget *pButton, gpointer data)
{
    // Process captured image to be saved on PBM format (codec P4)
    system("./image_processing");

    // Simplification data attribution (seuil as input)
    MethodData *methodData = (MethodData *)malloc(sizeof(MethodData));
    methodData->pVBox = GTK_WIDGET(data);
    methodData->method = "bezier2";
    show_input_dialog(pButton, methodData);
}

// Function callback executed when the "Bezier ordre 3" button is clicked
void bezier3_clicked(GtkWidget *pButton, gpointer data)
{
    // Process captured image to be saved on PBM format (codec P4)
    system("./image_processing");
    
    // Simplification data attribution (seuil as input)
    MethodData *methodData = (MethodData *)malloc(sizeof(MethodData));
    methodData->pVBox = GTK_WIDGET(data);
    methodData->method = "bezier3";
    show_input_dialog(pButton, methodData);
}

// Function callback executed when the "Cartoonize" button is clicked
void cartoonize_clicked(GtkWidget *pButton, gpointer data)
{
    // Process captured image with cartoonize script
    system("./cartoon");

    // Show message dialog after cartoonizing
    GtkWidget *message_dialog;
    message_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(data))),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK,
                                            "Thank you for using our Cartoonize processor. You can now try the simplifications for the new image. Please note that the previous image has not been saved.");
    gtk_dialog_run(GTK_DIALOG(message_dialog));
    gtk_widget_destroy(message_dialog);

    // Update UI to show new options
    check_image_and_update_ui(GTK_WIDGET(data));
}

// Function to show options when an image is found
void show_image_found_options(GtkWidget *pVBox)
{
    GtkWidget *pLabel, *cartoonizeLabel, *cartoonizeButton, *segments, *bezier2, *bezier3, *exitfile, *captureimage, *pImage;

    // Creation des labels
    pLabel = gtk_label_new("Choose the method that you wish to be used in order to simplify the captured image");
    cartoonizeLabel = gtk_label_new("For better results you can try to cartoonize the image");

    // Creation des boutons
    cartoonizeButton = gtk_button_new_with_label("Cartoonize");
    segments = gtk_button_new_with_label("Segments");
    bezier2 = gtk_button_new_with_label("Bezier ordre 2");
    bezier3 = gtk_button_new_with_label("Bezier ordre 3");
    captureimage = gtk_button_new_with_label("Capture new image");
    exitfile = gtk_button_new_with_label("Exit");
    pImage = gtk_image_new_from_file("logo.png");

    // Insertion des widgets dans la GtkVBox
    gtk_box_pack_start(GTK_BOX(pVBox), cartoonizeLabel, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), cartoonizeButton, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), segments, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), bezier2, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), bezier3, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), captureimage, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), exitfile, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pImage, TRUE, FALSE, 0);

    // Connexion du signal "clicked" du GtkButton
    g_signal_connect(G_OBJECT(cartoonizeButton), "clicked", G_CALLBACK(cartoonize_clicked), (GtkWidget *)pVBox);
    g_signal_connect(G_OBJECT(segments), "clicked", G_CALLBACK(segments_clicked), (GtkWidget *)pVBox);
    g_signal_connect(G_OBJECT(bezier2), "clicked", G_CALLBACK(bezier2_clicked), (GtkWidget *)pVBox);
    g_signal_connect(G_OBJECT(bezier3), "clicked", G_CALLBACK(bezier3_clicked), (GtkWidget *)pVBox);
    g_signal_connect(G_OBJECT(captureimage), "clicked", G_CALLBACK(image_capture_clicked), pVBox);
    g_signal_connect(G_OBJECT(exitfile), "clicked", G_CALLBACK(gtk_main_quit), NULL);
}

// Function to show options when no image is found
void show_no_image_found_options(GtkWidget *pVBox)
{
    GtkWidget *pLabel, *actionButton, *exitfile, *pImage;

    // Creation du label et du bouton pour l'autre cas
    pLabel = gtk_label_new("No image was found on the directory. Please try capture one.");
    actionButton = gtk_button_new_with_label("Capture new image");
    exitfile = gtk_button_new_with_label("Exit");
    pImage = gtk_image_new_from_file("logo.png");

    // Insertion des widgets dans la GtkVBox
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), actionButton, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), exitfile, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pImage, TRUE, FALSE, 0);

    // Connexion du signal "clicked" du GtkButton
    g_signal_connect(G_OBJECT(actionButton), "clicked", G_CALLBACK(image_capture_clicked), pVBox);
    g_signal_connect(G_OBJECT(exitfile), "clicked", G_CALLBACK(gtk_main_quit), NULL);
}

// Function to show the default page
void show_default_page(GtkWidget *pVBox)
{
    GtkWidget *pLabel, *startButton, *pImage;

    // Creation du label et du bouton pour la page par défaut
    pLabel = gtk_label_new("Welcome to the image capture application.");
    pImage = gtk_image_new_from_file("logo.png");
    startButton = gtk_button_new_with_label("Let's go");

    // Insertion des widgets dans la GtkVBox
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pImage, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), startButton, TRUE, FALSE, 0);

    // Connexion du signal "clicked" du GtkButton
    g_signal_connect(G_OBJECT(startButton), "clicked", G_CALLBACK(image_capture_clicked), pVBox);
}

// Function to check for the image and update the UI accordingly
void check_image_and_update_ui(GtkWidget *pVBox)
{
    gboolean image_found = tmp_image_found("tmp3209803-ext34V3");

    // Remove all children from pVBox
    GList *children = gtk_container_get_children(GTK_CONTAINER(pVBox));
    for (GList *iter = children; iter != NULL; iter = g_list_next(iter))
    {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    if (image_found)
    {
        show_image_found_options(pVBox);
    }
    else
    {
        show_no_image_found_options(pVBox);
    }

    // Show all widgets in pVBox
    gtk_widget_show_all(pVBox);
}

// Function callback for the "Let's go" button
void image_capture_clicked(GtkWidget *pButton, gpointer data)
{
    GtkWidget *pVBox = GTK_WIDGET(data);

    g_print("Console: image_capture program was called\n");
    // Non-blocking
    // Non-blocking execution
    GError *error = NULL;
    if (!g_spawn_command_line_async("./image_capture", &error))
    {
        g_print("Error executing image_capture: %s\n", error->message);
        g_error_free(error);
    }

    // Give some time for the image capture to complete before checking
    g_timeout_add(2000, (GSourceFunc)check_image_and_update_ui, pVBox);
}

int main(int argc, char *argv[])
{
    GtkWidget *pWindow, *pVBox, *pScrolledWindow;

    gtk_init(&argc, &argv);

    // Set a fixed size for the window (e.g., 500x700 pixels)
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 500, 700);

    gtk_window_set_title(GTK_WINDOW(pWindow), "ImagePulser V5.2.1");

    // Create a scrolled window
    pScrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(pWindow), pScrolledWindow);

    // Create a VBox and add it to the scrolled window
    pVBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(pScrolledWindow), pVBox);

    show_default_page(pVBox);

    gtk_widget_show_all(pWindow);

    // Prevent the user from resizing the window
    gtk_window_set_resizable(GTK_WINDOW(pWindow), FALSE);

    // Connect the delete event to allow closing the window with the window manager
    g_signal_connect(G_OBJECT(pWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    // Deleting tmp file
    remove("tmp3209803-ext34V3");
    return 0;
}
