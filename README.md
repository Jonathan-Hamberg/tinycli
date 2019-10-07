# tinycli

Tinycli is a small C library for providing a simple command line interface
to resource constrained embedded systems. The library is designed to be small,
lightweight, and extremely portable while still containing a useful feature
set for interacting with microcontrollers via a terminal interface.

Tinycli works by directly mapping a text command to a C function.


## Quickstart


```C
void doSomething(int a, double b, int c) {
    printf("I'm a function!! %d %f %d\n", a, b, c);
}
```

```C
tinycli_register("doit", doSomething, idi)
```

## Usage

Commands in Tinycli are statically declared at compile time via the tinycli-funs.h
header file.


### Registering a command

```C
tinycli_register("command string", function_name, parameter_types)
```

where the `parameter_type` is a descriptor of the types of arguments the
function is expecting. This is used to automatically convert the string inputs
to the correct type for passing into the function.

| Type        | Code | Example |
|-------------|------|---------|
| `void`      | `v`  |         |
| `int`       | `i`  | 12      |
| `double`    | `d`  | 3.14    |
| `char*`     | `s`  | hello   |
| `long long` | `ll` | 9999999 |

### Passing text
```C
void tinycli_putsn(char* s, int n);
void tinycli_putc(char c);
```
### Checking Results
```C
assert(tinycli_result == 1);
```

## Configuring TinyCli ##





## Extending TinyCli ##
TinyCli has beed designed to support a limited set of input data types and
a limited number of command arguments. In the event that additional data types
or additional command arguments are needed, TinyCli can easily be extended
to support any needed types or number of arguments.


#### New Data Types ####
Currently supported data types are: `int`, `double`, `long long`, and `char*`.
To add support for an additional type, write a conversion function from `char*`
to the new type, and register the new type with the various TinyCli macros.
These steps are described in further detail below.

Each supported data type is represented by a type code. When adding a new
data type, a new type code needs to be chosen. Generally, these should be
related to the C++ name mangling scheme, but any valid C identifier will
work.

##### Registering Type Code #####
Once a type code has been chosen, it needs to be registered with TinyCli by
adding it to the `tinycli_types_*` and `tinycli_nargs_*` macros in `tinycli.c`.
The former tells us the mapping between type code and C type; the latter
is a book keeping macro for internal use. These should be of the form:

```C
#define tinycli_types_<code>   <type>
```

```C
#define tinycli_nargs_<code>(...)    tinycli_lastarg(__VA_ARGS__)
```

where `<code>` is the chosen type code and `<type>` is the C data type.
`tinycli_types_<code>` should register the C type being added, while
`tinycli_nargs_<code>` should be added unmodified except for the specific
type code.


##### Conversion Function #####
In order to call a registered function with the correct parameters, TinyCli
needs a conversion function for each supported type. These conversion
functions are of the form:

```C
<type> tinycli_sto<code>(const char* s) {
    // TODO: do conversion
}
```

where `<type>` is the C type that the argument is being converted to and
`<code>` is the type code representing this new type. Implement a new
conversion function for the desired type and place it in `tinycli.c` near the
other `tinycli_sto*` functions. Note that the name of the function is
important and must match the above scheme exactly.


#### Increasing Max Number of Arguments ####
By default, TinyCli supports a limited number of arguments per command. To
increase this number, we need to edit a few macros in `tinycli.c`.

##### Argument Counting Macros #####
The first set of macros to edit are the argument counting macros
`tinycli_nargs` and `tinycli_lastarg`. These macros use `__VA_ARGS__` to count
the number of function parameters each registered function expects. To update
them for increased maxiumum numbers of arguments, simply increase the range
of the number sequences in each macro. For `tinycli_nargs` this means adding
numbers after the second `__VA_ARGS__` such that the maximum in the range
equals the maximum number of supported arguments. For `tinycli_lastarg` this
means adding additional numbered arguments (note the underscore) at the end
of the sequence (before the `...`). The maximum of the macro numbered arguments
should equal two more than the maximum number of supported arguments.
Additionally, change the ending numbered argument to match the maximum in
the range. For example, to change from 5 supported arguments to 6 the macros
would be be changed like so:

```C
#define tinycli_lastarg(_1, _2, _3, _4, _5, _6, _7, ...) _7
#define tinycli_nargs(...) CONCAT(tinycli_nargs_,FIRST(__VA_ARGS__))(_, ## __VA_ARGS__, 5, 4, 3, 2, 1, 0)
```
becomes
```C
#define tinycli_lastarg(_1, _2, _3, _4, _5, _6, _7, _8, ...) _8
#define tinycli_nargs(...) CONCAT(tinycli_nargs_,FIRST(__VA_ARGS__))(_, ## __VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)
```


##### Parameter & Args Conversion Macros #####
The second set of macros to edit are the params and args conversion macros.
These sections have a macro defined for each possible number of command
arguments. When increasing the maximum supported number of arguments, we add
an additional line for each new number of possible arguments. These macros
take the form:

```C
#define tinycli_params_<num>(t, ...) tinycli_types_##t, tinycli_params_<num-1>(__VA_ARGS__)
#define tinycli_args_<num>(n,i,t, ...) CONCAT(tinycli_sto,t)(argv[(n) - ((i)-1)]), tinycli_args_<num-1>(n, i-1,__VA_ARGS__)
```

where `<num>` is the new number of supported arguments. When adding a
new macro, all that is changed is this number. Each macro references the macro
with the previous number as seen by the `<n-1>`. As an example, if increasing
the max number of arguments from 5 to 7, we would add new macros for both 6
and 7.



