/* scanner .h*/
#ifndef __HEADERFORFLEX__H
#define __HEADERFORFLEX__H

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
	lx_eq, lx_neq, lx_lt, lx_le, lx_gt, lx_ge,lx_eof,lx_error
}
LEXEME_TYPE;

// Definition of TOKEN, you can use a clase if you  want 

typedef struct TOKEN {
    int type;
    int value;
    float float_value;
    char *str_ptr;
} TOKEN;

class SCANNER{
   private:
    // define your functions ..
    //I would define the following functions..
    // void skip_comments();
    // bool check_keyword(...)
    // TOKEN *get_id(..)
    // TOKEN *get_string(..)
    // TOKEN *get_int(..) // gets integers and floats

	public:
	SCANNER();

	TOKEN* Scan(); 
    // You may define it as TOKEN *Scan(FileDescriptor *fd);

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

#endif




