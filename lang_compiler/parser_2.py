from functools import reduce
import os
import ply.yacc

from lang_lexer import tokens
from lang_module import LangModule
from lang_symbol import Symbol


module = LangModule()

compiled_path = os.path.join(os.getcwd(), 'compiled.c')


def compile_number_literals():
    global module
    ns = module.init.scope.literals['number']

    if len(ns) == 0:
        return

    values = map(lambda sym: sym.value, ns)
    vals = reduce(lambda code, val: code + str(float(val)) + ',', values, '')

    module.init.add_line(f'object_t* number_literals[{len(ns)}];')
    module.init.add_line(f'double number_literal_values[{len(ns)}] = ' + '{ ' + vals + ' };')

    module.prepare.add_line(f'for (long i = 0; i < {len(ns)}; i++)')
    module.prepare.add_line('{')
    module.prepare.add_line(f'\tnumber_literals[i] = number_api._create(number_literal_values + i);')
    module.prepare.add_line('}\n')


# binary ops - create temps
def compile_arith_op(left: Symbol, op: str, right: Symbol):
    global module

    sym = module.run.scope.add_temp('arith_op', op)

    ops_method_names = {
        '+': 'add',
        '-': 'subtract',
        '*': 'multiply',
        '/': 'divide'
    }

    res = f'object_t* {sym.name} = number_api._ops.{ops_method_names[op]}({left.name}, {right.name});\n'

    sym.line = module.run.add_line(res)

    return sym

def compile_compare_op(left: Symbol, op, right: Symbol):
    global module

    # temp type should be the type of the op res (number)
    sym = module.run.scope.add_temp('compare_op', op)

    ops_method_names = {
        '==': 'cmp_eq',
        '>=': 'cmp_ge'
    }


    res = f'bool_t {sym.name} = number_api._ops.{ops_method_names[op]}({left.name}, {right.name});\n'

    sym.line = module.run.add_line(res)

    return sym

# returns the name which is now the new statement
def compile_init(name: Symbol, value: Symbol):
    global module

    name.symbol_type = value.symbol_type

    res = f'object_t* {name.name} = {value.name};'
    name.value = res

    name.line = module.run.add_line(res)
    return name 


# replace the statement line with the if 'line' but still is a stmt
def compile_if(condition: Symbol, statement: Symbol):
    res = f'if ({condition.name}) ' + '{\n\t' + statement.value + '\n}'

    lines_after = module.run.body[:statement.line:] + [res] + module.run.body[statement.line + 1::]

    module.run.body = lines_after
    statement.value = res
    return statement


def examine_name(name: str):
    sym = next((s for s in module.run.scope.names if s.name == name), None)

    if sym is not None:
        return sym

    return module.run.scope.add_name(name, 'name', None)

def compile_fn_defn(name: Symbol, params, rv_type, body):
    pass

def compile():
    global module

    # should be a dedicated boilerplate method
    module.init.add_line('#include "primitives.h"\n\n\n')

    compile_number_literals()
    # compile string, list, dict literals
    with open(compiled_path, 'w+') as file:
        file.write(str(module))

# end compiler
# 
# 
# 
# 
# 
# parser

precedence = [
    ('left', 'initialize'),
    ('left', 'arith_op'),
    ('left', 'compare_op'),
]

def p_error(p):
    print('error', p)


# statements

def p_program(p):
    ''' program : stmt 
    | program stmt '''
    p[0] = (p[1]) if len(p) == 2 else (p[1], p[2])

def p_stmt_line(p):
    ''' stmt : stmt newline '''
    # also add the line... if not added
    p[0] = p[1]

def p_stmt_init(p):
    ''' stmt : expr initialize expr '''
    p[0] = compile_init(p[1], p[3])

def p_stmt_if(p):
    ''' stmt : if expr stmt '''
    p[0] = compile_if(p[2], p[3])

# def p_stmt_scope(p):
#     ''' stmt : '{' newline stmt '}' '''
#     p[0] = p[3]

# fn my_func(number arg1, string arg2, bool arg3) -> number {
#   
# }
def p_stmt_fn_defn(p):
    ''' stmt : fn name '(' params ')' rv_type name '{' stmt '}' '''
    print(f'fn defn {p=}')
    p[0] = compile_fn_defn(p[2], p[4], p[7], p[8])

def p_stmt_param(p):
    ''' params : 
    | expr expr  
    | params ',' expr expr 
    '''
    print(f'params {p=}')
    p[0] = None if len(p) == 2 else (p[1], p[2]) if len(p) == 3 else (p[1], p[3], p[4])

# expressions

def p_expr_name(p):
    ''' expr : name '''
    p[0] = examine_name(p[1])
    

def p_expr_number(p):
    ''' expr : number '''
    p[0] = module.init.scope.add_literal('number', p[1])


def p_expr_string(p):
    ''' expr : string '''
    p[0] = module.init.scope.add_literal('string', p[1])

def p_expr_fn_call(p):
    ''' expr : name '(' commas ')' '''


def p_compare_expr(p):
    ''' expr : expr compare_op expr '''
    p[0] =  compile_compare_op(p[1], p[2], p[3])

def p_arith_expr(p):
    ''' expr : expr arith_op expr '''
    p[0] = compile_arith_op(p[1], p[2], p[3])
    
def p_expr_commas(p):
    ''' commas :  
     |  expr 
     | commas ',' expr
    '''
    p[0] = None if len(p) == 3 else (p[1]) if len(p) == 2 else (p[1], p[2])

parser: ply.yacc.LRParser = ply.yacc.yacc()

langcode: str = '''x <- 4 * 5 
    y <- x - 1 
    
    fn my_func (number a, number b) -> number {
        a - b
    }

    if (y == 19) {
        if (x >= 19) {
            z <- my_func(x, y)
        }
    }    
'''

langcode_fn_defn = 'fn my_func(number a, number b) -> number { c <- a * b }'

langcode_fn_call = 'my_func(x)'

tree = parser.parse(input=langcode_fn_defn, debug=True)

print(tree)
compile()
