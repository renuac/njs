
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) NGINX, Inc.
 */

#ifndef _NJS_LEXER_H_INCLUDED_
#define _NJS_LEXER_H_INCLUDED_


typedef enum {
    NJS_TOKEN_AGAIN = -2,
    NJS_TOKEN_ERROR = -1,
    NJS_TOKEN_ILLEGAL = 0,

    NJS_TOKEN_END,
    NJS_TOKEN_SPACE,
    NJS_TOKEN_LINE_END,

    NJS_TOKEN_DOUBLE_QUOTE,
    NJS_TOKEN_SINGLE_QUOTE,

    NJS_TOKEN_OPEN_PARENTHESIS,
    NJS_TOKEN_CLOSE_PARENTHESIS,
    NJS_TOKEN_OPEN_BRACKET,
    NJS_TOKEN_CLOSE_BRACKET,
    NJS_TOKEN_OPEN_BRACE,
    NJS_TOKEN_CLOSE_BRACE,

    NJS_TOKEN_COMMA,
    NJS_TOKEN_DOT,
    NJS_TOKEN_ELLIPSIS,
    NJS_TOKEN_SEMICOLON,

    NJS_TOKEN_COLON,
    NJS_TOKEN_CONDITIONAL,

    NJS_TOKEN_ASSIGNMENT,
    NJS_TOKEN_ARROW,
    NJS_TOKEN_ADDITION_ASSIGNMENT,
    NJS_TOKEN_SUBSTRACTION_ASSIGNMENT,
    NJS_TOKEN_MULTIPLICATION_ASSIGNMENT,
    NJS_TOKEN_EXPONENTIATION_ASSIGNMENT,
    NJS_TOKEN_DIVISION_ASSIGNMENT,
    NJS_TOKEN_REMAINDER_ASSIGNMENT,
    NJS_TOKEN_LEFT_SHIFT_ASSIGNMENT,
    NJS_TOKEN_RIGHT_SHIFT_ASSIGNMENT,
    NJS_TOKEN_UNSIGNED_RIGHT_SHIFT_ASSIGNMENT,
    NJS_TOKEN_BITWISE_OR_ASSIGNMENT,
    NJS_TOKEN_BITWISE_XOR_ASSIGNMENT,
    NJS_TOKEN_BITWISE_AND_ASSIGNMENT,

#define NJS_TOKEN_LAST_ASSIGNMENT   NJS_TOKEN_BITWISE_AND_ASSIGNMENT

    NJS_TOKEN_EQUAL,
    NJS_TOKEN_STRICT_EQUAL,
    NJS_TOKEN_NOT_EQUAL,
    NJS_TOKEN_STRICT_NOT_EQUAL,

    NJS_TOKEN_ADDITION,
    NJS_TOKEN_UNARY_PLUS,
    NJS_TOKEN_INCREMENT,
    NJS_TOKEN_POST_INCREMENT,

    NJS_TOKEN_SUBSTRACTION,
    NJS_TOKEN_UNARY_NEGATION,
    NJS_TOKEN_DECREMENT,
    NJS_TOKEN_POST_DECREMENT,

    NJS_TOKEN_MULTIPLICATION,

    NJS_TOKEN_EXPONENTIATION,

    NJS_TOKEN_DIVISION,

    NJS_TOKEN_REMAINDER,

    NJS_TOKEN_LESS,
    NJS_TOKEN_LESS_OR_EQUAL,
    NJS_TOKEN_LEFT_SHIFT,

    NJS_TOKEN_GREATER,
    NJS_TOKEN_GREATER_OR_EQUAL,
    NJS_TOKEN_RIGHT_SHIFT,
    NJS_TOKEN_UNSIGNED_RIGHT_SHIFT,

    NJS_TOKEN_BITWISE_OR,
    NJS_TOKEN_LOGICAL_OR,

    NJS_TOKEN_BITWISE_XOR,

    NJS_TOKEN_BITWISE_AND,
    NJS_TOKEN_LOGICAL_AND,

    NJS_TOKEN_BITWISE_NOT,
    NJS_TOKEN_LOGICAL_NOT,

    NJS_TOKEN_IN,
    NJS_TOKEN_INSTANCEOF,
    NJS_TOKEN_TYPEOF,
    NJS_TOKEN_VOID,
    NJS_TOKEN_NEW,
    NJS_TOKEN_DELETE,
    NJS_TOKEN_YIELD,

    NJS_TOKEN_DIGIT,
    NJS_TOKEN_LETTER,

#define NJS_TOKEN_FIRST_CONST     NJS_TOKEN_NULL

    NJS_TOKEN_NULL,
    NJS_TOKEN_NUMBER,
    NJS_TOKEN_BOOLEAN,
    NJS_TOKEN_STRING,

#define NJS_TOKEN_LAST_CONST      NJS_TOKEN_STRING

    NJS_TOKEN_ESCAPE_STRING,
    NJS_TOKEN_UNTERMINATED_STRING,
    NJS_TOKEN_NAME,

    NJS_TOKEN_OBJECT,
    NJS_TOKEN_OBJECT_VALUE,
    NJS_TOKEN_PROPERTY,
    NJS_TOKEN_PROPERTY_INIT,
    NJS_TOKEN_PROPERTY_DELETE,
    NJS_TOKEN_PROPERTY_GETTER,
    NJS_TOKEN_PROPERTY_SETTER,
    NJS_TOKEN_PROTO_INIT,

    NJS_TOKEN_ARRAY,

    NJS_TOKEN_GRAVE,
    NJS_TOKEN_TEMPLATE_LITERAL,

    NJS_TOKEN_FUNCTION,
    NJS_TOKEN_FUNCTION_EXPRESSION,
    NJS_TOKEN_FUNCTION_CALL,
    NJS_TOKEN_METHOD_CALL,
    NJS_TOKEN_ARGUMENT,
    NJS_TOKEN_RETURN,

    NJS_TOKEN_REGEXP,

    NJS_TOKEN_EXTERNAL,

    NJS_TOKEN_STATEMENT,
    NJS_TOKEN_BLOCK,
    NJS_TOKEN_VAR,
    NJS_TOKEN_IF,
    NJS_TOKEN_ELSE,
    NJS_TOKEN_BRANCHING,
    NJS_TOKEN_WHILE,
    NJS_TOKEN_DO,
    NJS_TOKEN_FOR,
    NJS_TOKEN_FOR_IN,
    NJS_TOKEN_BREAK,
    NJS_TOKEN_CONTINUE,
    NJS_TOKEN_SWITCH,
    NJS_TOKEN_CASE,
    NJS_TOKEN_DEFAULT,
    NJS_TOKEN_WITH,
    NJS_TOKEN_TRY,
    NJS_TOKEN_CATCH,
    NJS_TOKEN_FINALLY,
    NJS_TOKEN_THROW,

    NJS_TOKEN_THIS,
    NJS_TOKEN_NON_LOCAL_THIS,
    NJS_TOKEN_ARGUMENTS,
    NJS_TOKEN_EVAL,

#define NJS_TOKEN_FIRST_OBJECT     NJS_TOKEN_GLOBAL_OBJECT

    NJS_TOKEN_GLOBAL_OBJECT,
    NJS_TOKEN_NJS,
    NJS_TOKEN_PROCESS,
    NJS_TOKEN_MATH,
    NJS_TOKEN_JSON,

    NJS_TOKEN_OBJECT_CONSTRUCTOR,
    NJS_TOKEN_ARRAY_CONSTRUCTOR,
    NJS_TOKEN_BOOLEAN_CONSTRUCTOR,
    NJS_TOKEN_NUMBER_CONSTRUCTOR,
    NJS_TOKEN_STRING_CONSTRUCTOR,
    NJS_TOKEN_FUNCTION_CONSTRUCTOR,
    NJS_TOKEN_REGEXP_CONSTRUCTOR,
    NJS_TOKEN_DATE_CONSTRUCTOR,
    NJS_TOKEN_ERROR_CONSTRUCTOR,
    NJS_TOKEN_EVAL_ERROR_CONSTRUCTOR,
    NJS_TOKEN_INTERNAL_ERROR_CONSTRUCTOR,
    NJS_TOKEN_RANGE_ERROR_CONSTRUCTOR,
    NJS_TOKEN_REF_ERROR_CONSTRUCTOR,
    NJS_TOKEN_SYNTAX_ERROR_CONSTRUCTOR,
    NJS_TOKEN_TYPE_ERROR_CONSTRUCTOR,
    NJS_TOKEN_URI_ERROR_CONSTRUCTOR,
    NJS_TOKEN_MEMORY_ERROR_CONSTRUCTOR,

    NJS_TOKEN_IMPORT,
    NJS_TOKEN_EXPORT,

    NJS_TOKEN_RESERVED,
} njs_token_t;


typedef struct {
    njs_token_t                     token:16;
    uint32_t                        token_line;
    uint32_t                        key_hash;
    njs_str_t                       text;
    double                          number;
    njs_queue_link_t                link;
} njs_lexer_token_t;


typedef struct {
    njs_lexer_token_t               *lexer_token;
    njs_queue_t                     preread; /*  of njs_lexer_token_t */
    uint8_t                         keyword;

    u_char                          *prev_start;
    njs_token_t                     prev_token:16;

    uint32_t                        line;
    njs_str_t                       file;

    njs_lvlhsh_t                    keywords_hash;

    u_char                          *start;
    u_char                          *end;
} njs_lexer_t;


typedef struct {
    njs_str_t                       name;
    njs_token_t                     token;
    double                          number;
} njs_keyword_t;


njs_int_t njs_lexer_init(njs_vm_t *vm, njs_lexer_t *lexer, njs_str_t *file,
    u_char *start, u_char *end);
njs_token_t njs_lexer_token(njs_vm_t *vm, njs_lexer_t *lexer);
njs_token_t njs_lexer_peek_token(njs_vm_t *vm, njs_lexer_t *lexer,
    size_t offset);
njs_int_t njs_lexer_rollback(njs_vm_t *vm, njs_lexer_t *lexer);
njs_int_t njs_lexer_keywords_init(njs_mp_t *mp, njs_lvlhsh_t *hash);
void njs_lexer_keyword(njs_lexer_t *lexer, njs_lexer_token_t *lt);


#endif /* _NJS_LEXER_H_INCLUDED_ */
