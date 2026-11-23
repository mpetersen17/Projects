import tkinter as tk
from tkinter import ttk, filedialog
from lexer import scan

def analyze_input():
    source = source_box.get("1.0", "end-1c")

    tokens, symbol_table, errors = scan(source)

    status_label.config(
        text=(
            f"Tokens: {len(tokens)} | "
            f"Identifiers: {len(symbol_table)} | "
            f"Errors: {len(errors)}"
        )
    )

    # Temporary output for checking the connection.
    token_table.delete(*token_table.get_children())
    for item in tokens:
        token_table.insert("", "end", values=(item["token"], item["lexeme"], item["line"], item["column"]))


    symbol_table_view.delete(*symbol_table_view.get_children())
    for item in symbol_table:
        symbol_table_view.insert("", "end", values=(item["id"], item["name"], item["first_line"], item["first_column"], item["occurrences"]))

    error_table.delete(*error_table.get_children())
    for item in errors:
        error_table.insert("", "end", values=(item["lexeme"], item["line"], item["column"], item["message"]))

def clear_all():
    token_table.delete(*token_table.get_children())
    symbol_table_view.delete(*symbol_table_view.get_children())
    error_table.delete(*error_table.get_children())
    source_box.delete("1.0","end")
    status_label.config("Ready ")

def open_file():
    path = filedialog.askopenfilename()
    if not path:
        return 

    with open(path, "r", encoding="utf-8") as file:
        text = file.read()

    source_box.delete("1.0", "end")
    source_box.insert("1.0", text)




#The window build
window = tk.Tk()
window.title("Clite Lexical Analyzer")
window.geometry("900x650")

main_frame = ttk.Frame(window, padding=20)
main_frame.pack(fill="both", expand=True)

title_label = ttk.Label(
    main_frame,
    text="Clite Lexical Analyzer",
    font=("Arial", 20, "bold")
)
title_label.pack(anchor="w", pady=(0, 15))

input_label = ttk.Label(
    main_frame,
    text="Enter Clite source code:"
)
input_label.pack(anchor="w")

source_box = tk.Text(
    main_frame,
    height=7,
    font=("Consolas", 12),
    wrap="none",
    undo=True
)
source_box.pack(fill="both", expand=True, pady=10)

source_box.insert(
    "1.0",
    "int main() {\n    count = 12;\n}"
)

button_frame = ttk.Frame(main_frame)
button_frame.pack(anchor="w")

analyze_button = ttk.Button(
    button_frame,
    text="Analyze",
    command=analyze_input
)
analyze_button.pack(side="left", padx=(0,10))

clear_button = ttk.Button(button_frame, text="Clear", command=clear_all)
clear_button.pack(side="left", padx=(0,10))

open_button = ttk.Button(button_frame, text="Open File", command=open_file )
open_button.pack(side="left")

status_label = ttk.Label(
    main_frame,
    text="Ready."
)
status_label.pack(anchor="w", pady=10)

token_table = ttk.Treeview(main_frame, columns=("t", "lex", "l", "c"), show="headings", height=5)
token_table.heading("t", text="Token")
token_table.heading("lex", text="Lexeme")
token_table.heading("l", text="Line")
token_table.heading("c", text="Column")
token_table.pack(fill="x", expand=True)

symbol_table_view = ttk.Treeview(main_frame, columns=("id", "name", "fline","fcolumn", "occurrences"), show="headings", height=4)
symbol_table_view.heading("id", text="ID")
symbol_table_view.heading("name", text="Name")
symbol_table_view.heading("fline", text="First Line")
symbol_table_view.heading("fcolumn", text="First Column")
symbol_table_view.heading("occurrences", text="Occurrences")
symbol_table_view.pack(fill="x", expand=True)

error_table = ttk.Treeview(main_frame, columns=("lexeme", "line", "column","message"), show="headings", height=3)
error_table.heading("lexeme",text="Lexeme")
error_table.heading("line",text="Line")
error_table.heading("column",text="Column")
error_table.heading("message",text="Message")
error_table.column("message", width=300)
error_table.pack(fill="x", expand=True)


window.mainloop()
