import ply.lex


reserved = {
    'usertype': 'usertype',
    'if': 'if',
    'else': 'else',
    'loop': 'loop',
    'has': 'has',
    'is': 'is',
    'fn': 'fn',
    'run': 'run'
}

tokens = ['name', 'number', 'bool', 'string', 'arith_op', 'logic_op', 'initialize', 'literal', 'compare_op', 'newline', 'rv_type'] + list(reserved.keys())

literals = ['(', ')', '[', ']', '{', '}', '.', ',']

t_ignore = ' \t'

def t_newline(t):
    r'\n+'
    t.lexer.lineno += t.value.count("\n")
    return t

def t_initialize(t):
    r'<-'
    return t

def t_rv_type(t):
    r'->'
    return t

def t_compare_op(t):
    r'==|<=|>=|!=|is|>|<'
    return t

def t_literal(t: ply.lex.LexToken):
    r'[\(\[\{\)\]\}.,]'
    t.type = t.value
    return t


def t_bool(t):
    r'true|false'
    return t

def t_name(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    if t.value in reserved:
        t.type = t.value
    return t

def t_arith_op(t):
    r'[\+\-\*\/\%]'
    return t

# this is a number literal, meaning I can name it by some count variable
# and I know the code for its decl / defn
def t_number(t):
    r'([0-9]*[.])?[0-9]+'
    t.value = float(t.value)
    return t

def t_error(t):
    print(f'error with {t=}')

def t_string(t):
    r'\'([^\\\"]|\\.)*\''
    return t


lexer: ply.lex.Lexer = ply.lex.lex()


# langcode: str = ''' (5) [!=] {6} '''

# lexer.input(langcode)
# while 1:
#     token = lexer.token()
#     if token is None:
#         break
#     print(f'{token=}')

