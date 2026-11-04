#pragma once
#include "FileDescriptor.h"
#include <ctype.h>
#include <vector>
#define SIZE(X) sizeof(X)/sizeof((X)[0])
//Token types enumeration
typedef enum
{
	/* Literals */
	lx_identifier, lx_integer, lx_string,lx_float,
	/* Keywords */
	kw_program,
	kw_var, kw_constant, kw_integer, kw_boolean, kw_string, kw_float,
	kw_true, kw_false, kw_if, kw_fi, kw_then, kw_else,
	kw_while, kw_do, kw_od,
	kw_and, kw_or, 
	kw_read, kw_write,
	kw_for, kw_from, kw_to, kw_by,
	kw_function, kw_procedure,kw_return, kw_not, kw_begin, kw_end,
	/* Operators */
	lx_Iparen, lx_rparen, lx_lbracket, lx_rbracket,
	Ix_colon, lx_dot, lx_semicolon, lx_comma, Ix_colon_eq,
	lx_plus, lx_minus, lx_star, lx_slash,
	lx_eq, lx_neq, lx_lt, lx_le, lx_gt, lx_ge,lx_eof,lx_error,
} LEXEME_TYPE;

// Definition of TOKEN, you can use a clase if you  want 
struct	TOKEN
{
	LEXEME_TYPE type;
	int value;  // can be used instead of the str_ptr for IDs and strings
	float float_value;
	
	char *str_ptr; // points to strings or Identifiers, can use value
	              //instead but with type casting
};


// It is helpful to define the following arrays in your .cpp file
// not in this header file

/* The keyword list is and must be kept in alphabetical order. To
add a keyword, insert it at the appropriate place in keyword[],
insert its type in the appropriate place in key type[], and
increment the var keys. Order is needed for binary search
*/
int keys = 32; /* number of keywords */
const char *keyword[] = {
"and", "begin", "boolean", "by", "constant",
"do", "else", "end", "false", "fi", "float", "for", "from",
"function", "if", "integer", "not", "od", "or", "procedure",
"program", "read", "return", "string", "then", "to", "true",
"var", "while", "write"
};

LEXEME_TYPE key_type[] = {
kw_and, kw_begin, kw_boolean, kw_by, kw_constant,
kw_do, kw_else, kw_end, kw_false, kw_fi,kw_float,
kw_for, kw_from, kw_function, kw_if, kw_integer, kw_not,
kw_od, kw_or, kw_procedure, kw_program,kw_read, kw_return,
kw_string, kw_then, kw_to, kw_true, kw_var, kw_while, kw_write
};


typedef struct {
    TOKEN* tokens = nullptr;
    int size = 0;
    int capacity = 2;
} TokenVector;



class Scanner{
    private:
    FileDescriptor fl;
    char* content;
    int line;
    int index;
    int BOS;
    TokenVector tokens;
    char peek(int shift = 0) {
        return content[index + shift];
    }
    void consume() {
        index++;
    }

    void addToken(TOKEN t){
        if(tokens.tokens == nullptr) {
            tokens.tokens = (TOKEN*)malloc(sizeof(TOKEN) * tokens.capacity);
        } 
        if(tokens.size >= tokens.capacity) {
            tokens.capacity *= 2;
            tokens.tokens = (TOKEN*)realloc(tokens.tokens,sizeof(TOKEN) *tokens.capacity );
        }
        tokens.tokens[tokens.size++] = t;
    }

    void printTokens() {
        for(size_t i = 0 ; i < tokens.size;i++) {

            if (tokens.tokens[i].type != lx_eof)
            {
                if(tokens.tokens[i].type == lx_integer || tokens.tokens[i].type == lx_float) {
                    fprintf(stdout,"%i.%i\n",tokens.tokens[i].value,tokens.tokens[i].float_value);
                } else {
                    fprintf(stdout,"%s\n",tokens.tokens[i].str_ptr);

                }
            }
            
        }
    }

    LEXEME_TYPE get_type(std::string buffer) {
        LEXEME_TYPE type = lx_identifier;
        for(int i = 0;i<SIZE(keyword);i++) {
            if(buffer == keyword[i]) {
                type = key_type[i];
                break;
            }
        }
        return type;
    }

    LEXEME_TYPE getOperatorType(char c) {
        switch (c)
        {
        case '+':
            return lx_plus;

        case '-':
            return lx_minus;
        case '*':
            return lx_star;
        case '/':
            return lx_slash;
        case '=':
            return lx_eq;
        case ':':
            return Ix_colon;
        case '>':
            return lx_gt;
        case '<':
            return lx_lt;

        }
    }

    LEXEME_TYPE getSymbolType(char c) {
        switch (c)
        {
        case '(':
            return lx_Iparen;

        case ')':
            return lx_rparen;

        case '[':
            return lx_lbracket;

        case ']':
            return lx_rbracket;

        case ',':
            return lx_comma;

        case '.':
            return lx_dot;

        case ';':
            return lx_semicolon;

        default:
            return lx_eof;
        }
    }
    
    char* get_value(std::string buffer) {
        int size = buffer.size();
        char* str = (char*)malloc((size+1)*sizeof(char));
        for(size_t i = 0;i<size;i++) {
            str[i] = buffer[i];
        }
        str[size] = '\0';
        return str;
    }

    void reportError(const char * str) {
        for(int i = BOS + 1;content[i] != '\n' && content[i] != '\0';i++) {
            std::cout << content[i];
        }
        std::cout << std::endl;
        int col = index - BOS;
        for(int i = 1;i<col;i++) {
            std::cout << " ";
        }
        std::cout << "^\n";
        std::cerr << str << " line:"<< line <<" column:"<<col <<std::endl;
    }

    public:
    Scanner(FileDescriptor& f){
        fl = f;
        line = 1;
        index = 0;
        BOS = -1;
        content = fl.getBuffer();
    }
    void scan() {
        char c = peek();
        std::string buffer;
        while(c != '\0') {
            buffer.clear();
            int negative = 0;
            TOKEN token = {lx_eof,0,0,nullptr};
            token.float_value = token.value = 0;
            if(isalpha(c) || c == '_') {
                token.type = lx_identifier;
                buffer += c;
                consume();
                c =  peek();
                while(isalnum(c) || c == '_') {
                    buffer += c;
                    consume();
                    c = peek();
                }
                token.type = get_type(buffer);
                token.str_ptr = get_value(buffer);
                buffer.clear();
                
            } else if(isdigit(c) || (c == '-' && isdigit(peek(1)))) {
                if(c=='-') {
                    negative = 1;
                    consume();
                    c = peek();
                }
                token.type = lx_integer;
                token.value = token.value*10 + (c-'0');
                consume();
                c = peek();
                while(isdigit(c)) {
                    token.value = token.value*10 + (c-'0');
                    consume();
                    c = peek();
                }
                c =  peek();
                
                if(c == '.') {
                    consume();
                    c = peek();
                    if(isdigit(c)) {
                        token.type = lx_float;
                        token.float_value = token.float_value*10 + (c-'0');
                        consume();
                        c = peek();
                        while (isdigit(c))
                        {
                            token.float_value = token.float_value*10 + (c-'0');
                            consume();
                            c = peek();
                        }
                        if(isalpha(peek())) {
                            reportError("invalid token");
                            continue;
                        }
                        
                    } else {
                        reportError("Error: \"Bad floating point number\"");
                        continue;
                    }
                } else if (isalpha(peek())) {
                    c = peek();
                    reportError("invalid token");
                    while(isalnum(c)) {
                        consume();
                        c = peek();
                    } 
                    continue;
                }
                int factor = (negative)? -1 : 1;
                token.value = token.value * factor;
            } else if(c == '#') {
                consume();
                c = peek();
                if(c == '#') {
                    consume(); 

                    while(!(peek() == '#' && peek(1) == '#')) {
                        if(peek() == '\n') {
                            line++;
                            BOS = index;
                            index--;
                            // consume();
                            break;
                        } else if (peek() == '\0') {
                            std::cerr << "Error: short comment not closed w line "
                                    << line << std::endl;

                        }
                        consume();
                    }

                    consume();
                    consume();
                    c = peek();

                } else {
                    while(c != '\n') {
                        consume();
                        c = peek();
                    }
                    line++;
                    BOS = index;
                }

            } else if (c == '"') {
                token.type = lx_string;
                buffer += c;
                consume(); 
                c = peek();

                while (c != '"') {
                    
                    if (c == '\0') {
                        std::cerr << "Error: Unterminated string at line "
                                << line << std::endl;
                    }

                    if (c == '\n') {
                        std::cerr << "Error: String cannot contain newline at line "
                                << line << std::endl;
                    }

                    
                    if (c == '\\' && peek(1) == '\n') {
                        consume();
                        consume();
                        line++;
                        c = peek();
                        continue;
                    }

                    buffer += c;
                    consume();
                    c = peek();
                }

                consume();
                c = peek();
                buffer += '"';
                token.str_ptr = get_value(buffer);
                buffer.clear();

            } else if ( c == '(' || c == ')' || 
                        // c == '{' || c == '}' ||
                        c == '[' || c == ']' ||
                        c == ',' || c == '.' || c == ';' ) {
                
                    token.type = getSymbolType(c);
                    buffer += c;
                    token.str_ptr = get_value(buffer);
                    buffer.clear();
                    consume();
                    c = peek();
                    
                } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
                    token.type = getOperatorType(c);
                    buffer+= c;

                    
                    token.str_ptr = get_value(buffer);
                    buffer.clear();
                    consume();
                    c = peek();
                }
                
            else if (c == ':' || c == '<' || c == '>') {
                    buffer += c;
                    token.type = getOperatorType(c);
                    consume();
                    c = peek();
                    if(c == '=') {
                        buffer += c;
                        switch (token.type)
                        {
                        case Ix_colon:
                                token.type = Ix_colon_eq;
                                break;
                        case lx_gt:
                                token.type = lx_ge;
                                break;

                        case lx_lt:
                                token.type = lx_le;
                                break;                 
                        }
                        consume();
                        c = peek();
                    }
                    token.str_ptr = get_value(buffer);
                    buffer.clear();
                    

            } else if (c == '!' && peek(1) =='=') {
                buffer += c;
                buffer += peek(1);
                token.type = lx_neq;
                token.str_ptr = get_value(buffer);
                buffer.clear();
                consume();
                consume();
                c = peek();
            }
            
            else if(isspace(c)){
                if(c =='\n') {
                    line++;
                    BOS = index;
                }
                consume();
                c = peek();
                continue;
            } else {
                token.type = lx_error;
                reportError("unknown char");
                consume();
                c = peek();
                buffer.clear();
                continue;
            }
            addToken(token);
        }
        addToken({lx_eof,0,0,nullptr});
        
        printTokens();
        fprintf(stdout,"size is %i\n",tokens.size);
    }
};



