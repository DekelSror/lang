from dataclasses import dataclass


@dataclass
class Symbol:
    name: str
    value: object
    symbol_type: str
    index: int
    line: int



def get_compiled(sym: Symbol):
    if sym.name == 'literal':
        return f'{sym.symbol_type}_literals[{sym.index}]'
    else:
        return sym.name