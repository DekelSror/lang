from functools import reduce

from lang_symbol import Symbol


class Scope:
    def __init__(self, parent) -> None:
        self.parent = parent
        self.names: list[Symbol] = []
        self.temps: list[Symbol] = []
        self.literals = {
            'number': [],
            'string': []
        }
        self.depth = 0
        if parent is not None:
            self.depth = parent.depth + 1
        

    def add_literal(self, atom_type: str, atom_value):
        index = len(self.literals[atom_type])
        sym = Symbol(f'{atom_type}_literals[{index}]', atom_value, atom_type, index, -1)
        self.literals[atom_type].append(sym)
        
        return sym

    def add_temp(self, temp_type, temp_value):
        index = len(self.temps)
        sym = Symbol('temp' + str(index), temp_value, temp_type, index, -1)
        self.temps.append(sym)

        return sym
        
    def add_name(self, id_name, id_type, id_value):
        sym = Symbol(id_name, id_value, id_type, len(self.names), -1)
        self.names.append(sym)

        return sym


class ModulePart:

    def __init__(self, name: str, scope: Scope) -> None:
        self.body: list[str] = []
        self.start = ''
        self.end = ''
        self.scope = scope
        self.part_name = name

        if name is not None:
            self.start = f'int {name}(void)\n' + '{\n'
            self.end = '\treturn 0;\n}\n\n'
        
        else:
            self.part_name = 'file_scope'
    
    def __repr__(self) -> str:
        return self.start + reduce(lambda s, line: s + line + '\n', self.body, '') + self.end

    def __str__(self) -> str:
        return self.__repr__()

    def tabulate(self, line: str):
        return '\t' * self.scope.depth + line

    def add_line(self, line: str):
        self.body.append(self.tabulate(line))

        return len(self.body) - 1

    
class LangModule:

    def __init__(self) -> None:
        self.init = ModulePart(None, Scope(None)) # file scope
        self.prepare = ModulePart('prepare', Scope(self.init.scope))
        self.run = ModulePart('main', Scope(self.init.scope))

        self.run.add_line('prepare();')

    def __str__(self) -> str:
        return str(self.init) + str(self.prepare) + str(self.run)


