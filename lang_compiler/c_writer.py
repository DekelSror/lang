


def cwrite_create(name, api, init_val):
    return f'object_t* {name} = {api}_api.create({init_val})'




def cwrite_fn_defn(name, rv_type, args, body):
    def cwrite_arg(arg_val, arg_type):
        res = 'fn_arg_t arg = ' + '{' + f'._type={arg_type}, ._next=0' + '}'
        


