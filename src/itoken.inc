//enum_info(n, s)
//n: name
//s: symbol

//placeholder
enum_info(unk,			nullptr)

//identifier
enum_info(id,			nullptr)

//literals
	enum_info(literal_start,nullptr)

	enum_info(l_string,		nullptr)
	enum_info(l_int,		nullptr)
	enum_info(l_uint,		nullptr)
	enum_info(l_real,		nullptr)

	//logical constants
	enum_info(l_true,		"true")
	enum_info(l_false,		"false")

	enum_info(literal_end,	nullptr)

//keywords
	enum_info(keyword_start,nullptr)

	//control keywords
	enum_info(k_if,			"if")
	enum_info(k_else,		"else")
	enum_info(k_while,		"while")
	enum_info(k_for,		"for")
	enum_info(k_do,			"do")
	enum_info(k_switch,		"switch")
	enum_info(k_case,		"case")
	enum_info(k_default,	"default")

	//manage keywords
	enum_info(k_import,		"import")
	enum_info(k_using,		"using")
	enum_info(k_extern,		"extern")

	enum_info(keyword_end,	nullptr)


//types
	enum_info(type_start,	nullptr)

	//normal types
	enum_info(t_int,		"int")
	enum_info(t_real,		"real")
	enum_info(t_bool,		"bool")
	enum_info(t_string,		"string")

	//integer types
	enum_info(t_i8,			"i8")
	enum_info(t_i16,		"i16")
	enum_info(t_i32,		"i32")
	enum_info(t_i64,		"i64")

	//unsigned integer types
	enum_info(t_ui8,		"ui8")
	enum_info(t_ui16,		"ui16")
	enum_info(t_ui32,		"ui32")
	enum_info(t_ui64,		"ui64")

	//float types
	enum_info(t_f32,		"f32")
	enum_info(t_f64,		"f64")

	enum_info(type_end,		nullptr)


//paired symbols
enum_info(lpare,		"(")
enum_info(rpare,		")")
enum_info(lbrack,		"[")
enum_info(rbrack,		"]")
enum_info(lbrace,		"{")
enum_info(rbrace,		"}")

//normal symbols
enum_info(assign,		"=")
enum_info(dot,			".")
enum_info(colon,		":")
enum_info(wrapper,		"->")
enum_info(quest,		"?")

//arithmetic operation
enum_info(add,			"+")
enum_info(sub,			"-")
enum_info(mul,			"*")
enum_info(div,			"/")
enum_info(mod,			"%")

//bitwise operation
enum_info(bit_and,		"&")
enum_info(bit_or,		"|")
enum_info(bit_xor,		"^")
enum_info(bit_not,		"~")

//logical operation
enum_info(logic_and,	"&&")
enum_info(logic_or,		"||")
enum_info(logic_not,	"!")

//relational operation
enum_info(equal,		"==")
enum_info(less,			"<")
enum_info(greater,		">")
enum_info(less_equal,	"<=")
enum_info(greater_equal,">=")

