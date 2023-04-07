import ply.yacc
from lang_lexer import tokens



precedence = (

)

names = {}

def p_error(p):
    print(f'parser error {p}')

def p_expr(p):
    '''a : number
     | name
     | string 
     | bool ''' 
    p[0] = p[1]


def p_unary(p):
    'a : arith_op number'
    number_val = float(p[2])
    if p[1] == '+':
        p[0] = +number_val
    else:
        p[0] = -number_val


def p_initialization(p):
    ''' a : name initialize expr '''
    names[p[1]] = p[3]

def p_fn_call_args(p):
    '''a : '(' name ')' '''
    print(f'{[x for x in p]}')

def p_fn_call(p):
    '''a : name '(' fn_call_args ')' '''
    print(f'{[x for x in p]}')

parser = ply.yacc.yacc(debug=True, debugfile='parser_debug')

input = 'x <- my_fn(-128, 4)'
print(f'{parser.parse(input)=}')