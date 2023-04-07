


def cwrite_init(name, api, init_val):
    return f'object_t* {name} = {api}_api.create({init_val})'




def cwrite_fn_defn(name, rv_type, args, body):
    def cwrite_arg(arg_val, arg_type):
        res = 'fn_args_t arg = ' + '{' + f'._type={arg_type}, ._next=0' + '}'
        

    
