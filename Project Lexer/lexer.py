"""Lexical analyzer for the supplied Clite grammar."""

KEYWORDS = {
    "int", "main", "bool", "float",
    "char", "if", "else", "while"
}

LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
DIGITS = "0123456789"

SYMBOLS = {
    "==": "EQUAL",
    "!=": "NOT_EQUAL",
    "<=": "LESS_EQUAL",
    ">=": "GREATER_EQUAL",
    "&&": "AND",
    "||": "OR",
    "=": "ASSIGN",
    "<": "LESS",
    ">": "GREATER",
    "!": "NOT",
    "+": "PLUS",
    "-": "MINUS",
    "*": "MULTIPLY",
    "/": "DIVIDE",
    "%": "MODULO",
    "(": "LPAREN",
    ")": "RPAREN",
    "{": "LBRACE",
    "}": "RBRACE",
    "[": "LBRACKET",
    "]": "RBRACKET",
    ",": "COMMA",
    ";": "SEMICOLON"
}


def classify_word(word):
    """Classify a complete word found by the scanner."""
    if word in KEYWORDS:
        return "KEYWORD"
    elif word in {"true", "false"}:
        return "BOOLEAN_LITERAL"
    else:
        return "IDENTIFIER"


def scan(source):
    """Return three lists: tokens, identifier symbols, and errors."""
    # Normalize Windows and older Mac line endings.
    source = source.replace("\r\n", "\n").replace("\r", "\n")

    tokens = []
    symbols = {}
    errors = []

    position = 0
    line = 1
    column = 1

    while position < len(source):
        character = source[position]

        # Skip whitespace, updating the source location.
        if character in " \t\n":
            if character == "\n":
                line += 1
                column = 1
            else:
                column += 1

            position += 1
            continue

        start = position
        start_line = line
        start_column = column
        token_type = None

        # Identifiers and reserved words.
        if character in LETTERS:
            position += 1

            while (
                position < len(source)
                and source[position] in LETTERS + DIGITS
            ):
                position += 1

            lexeme = source[start:position]
            token_type = classify_word(lexeme)

        # Integer or float literal.
        elif character in DIGITS:
            position += 1

            while (
                position < len(source)
                and source[position] in DIGITS
            ):
                position += 1

            token_type = "INTEGER_LITERAL"

            # A float requires digits on both sides of the dot.
            if (
                position + 1 < len(source)
                and source[position] == "."
                and source[position + 1] in DIGITS
            ):
                position += 1

                while (
                    position < len(source)
                    and source[position] in DIGITS
                ):
                    position += 1

                token_type = "FLOAT_LITERAL"

        # Character literal: one ASCII character in single quotes.
        elif character == "'":
            if (
                position + 2 < len(source)
                and source[position + 2] == "'"
                and source[position + 1] not in "\n\r"
                and ord(source[position + 1]) < 128
            ):
                position += 3
                token_type = "CHAR_LITERAL"
            else:
                # Recover at the closing quote or end of this line.
                position += 1

                while (
                    position < len(source)
                    and source[position] not in "'\n"
                ):
                    position += 1

                if (
                    position < len(source)
                    and source[position] == "'"
                ):
                    position += 1

                errors.append({
                    "lexeme": source[start:position],
                    "line": start_line,
                    "column": start_column,
                    "message": (
                        "Expected one ASCII character "
                        "inside single quotes."
                    )
                })

        # Longest match: try two-character operators first.
        elif source[position:position + 2] in SYMBOLS:
            lexeme = source[position:position + 2]
            token_type = SYMBOLS[lexeme]
            position += 2

        elif character in SYMBOLS:
            token_type = SYMBOLS[character]
            position += 1

        # Record unsupported characters and keep scanning.
        else:
            errors.append({
                "lexeme": character,
                "line": start_line,
                "column": start_column,
                "message": "Invalid character."
            })
            position += 1

        lexeme = source[start:position]
        column += position - start

        if token_type is not None:
            tokens.append({
                "token": token_type,
                "lexeme": lexeme,
                "line": start_line,
                "column": start_column
            })

            # Store each unique identifier once.
            if token_type == "IDENTIFIER":
                if lexeme not in symbols:
                    symbols[lexeme] = {
                        "id": len(symbols) + 1,
                        "name": lexeme,
                        "first_line": start_line,
                        "first_column": start_column,
                        "occurrences": 0
                    }

                symbols[lexeme]["occurrences"] += 1

    return tokens, list(symbols.values()), errors


def display_results(tokens, symbol_table, errors):
    """Display results when running this file directly."""
    print("\nTOKENS AND LEXEMES")
    print(f"{'TOKEN':<20} {'LEXEME':<18} {'LINE':<6} COLUMN")
    print("-" * 56)

    for item in tokens:
        print(
            f"{item['token']:<20} "
            f"{item['lexeme']!r:<18} "
            f"{item['line']:<6} "
            f"{item['column']}"
        )

    print("\nSYMBOL TABLE")
    print(
        f"{'ID':<5} {'IDENTIFIER':<16} "
        f"{'LINE':<6} {'COLUMN':<8} OCCURRENCES"
    )
    print("-" * 56)

    for symbol in symbol_table:
        print(
            f"{symbol['id']:<5} "
            f"{symbol['name']:<16} "
            f"{symbol['first_line']:<6} "
            f"{symbol['first_column']:<8} "
            f"{symbol['occurrences']}"
        )

    print("\nLEXICAL ERRORS")

    if not errors:
        print("None")
    else:
        for error in errors:
            print(
                f"Line {error['line']}, "
                f"column {error['column']}: "
                f"{error['message']} "
                f"Found {error['lexeme']!r}"
            )


if __name__ == "__main__":
    source = """int main() {
    count = 12;
    limit = 20;
    rate = 3.14;
    letter = 'A';
    enabled = true;
    finished = false;
    values[count] = count * 2 / 1 % 3;
    if (count >= limit || count == 0) {
        count = count - 1;
    } else {
        count = count + 1;
    }
    while (count < limit && !finished) {
        count = count + 1;
    }
    enabled = count != limit;
    enabled = count <= limit;
    enabled = count > limit;
    rate = float(count);
    enabled = bool(count);
    letter = char(count);
}"""

    tokens, symbol_table, errors = scan(source)
    display_results(tokens, symbol_table, errors)
 
