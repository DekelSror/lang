

## current goal is just to have working examples of all types, then move on to compiler

## notice that lists and dicts play two roles - they are c modules but are also
## types in the language



1. make functions into objects - can we tell the difference with 16 bytes?
2. memory for list vectors, dict tables, usertypes atts / methods,strings?
3. default sizes, expansion of vectors / tables
4. assigment like dict[key] = value ... does it brake the const? if so, what is the alternative
5. dict from list / list form dict 
6. string split / join / pattern-based functions

memory -

locals - on the stack?

lang_fn structs (with variable sizes due to fn_arg)
methods (same)

return values, values that pass by ref

elements in collections


does dict[key] <- newVal violates immutability? should we differentiate existing keys from new ones?

also object_api doesn't support assignment to element....
the concern here is the cutoff point between using the language with object_t and apis and using c_modules with regular void*