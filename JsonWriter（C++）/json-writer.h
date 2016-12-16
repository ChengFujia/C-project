#ifndef _JSONWRITER_H
#define _JSONWRITER_H
#include <iostream>
#include <string>
#include <stack>

class JsonWriter
{
public:
	//json最主要的两种类型 -- array + object
	enum ContainerType
	{
		CONTAINER_TYPE_ARRAY,
		CONTAINER_TYPE_OBJECT
	};

	//json的布局 -- 继承父类 + 多行元素 + 单行元素
	enum ContainerLayout
	{
		CONTAINER_LAYOUT_INHERIT,
		CONTAINER_LAYOUT_MULTI_LINE,
		CONTAINER_LAYOUT_SINGLE_LINE
	};

	//明确的，清晰的 -- 不允许 隐式转换时 使用该构造函数
	//c++11 特有的 构造函数方法
	explicit JsonWriter():      
        writer (NULL),
        initialIndentDepth (0),
        indent ("  "),
        containerPadding (" "),
        keyPaddingLeft (""),
        keyPaddingRight (" "),
        defaultContainerLayout (CONTAINER_LAYOUT_MULTI_LINE),
        forceDefaultContainerLayout (false) { }

	//如果需要 压缩 输出的json数据 -- 减少空格 + 减少换行
	void ConfigureCompressedOutput()
	{
		SetIndent("");
		SetContainerPadding("");
		SetKeyPaddingLeft("");
		SetKeyPaddingRight("");
		SetDefaultContainerLayout(CONTAINER_LAYOUT_SINGLE_LINE);
		SetForceDefaultContainerLayout(true);
	}

	//关于 缩进
	int GetInitialIndentDepth () { return initialIndentDepth; }
	void SetInitialIndentDepth(int depth) { initialIndentDepth = depth; }
	const char *GetIndent() { return indent; }
	void SetIndent(const char *indent) { this->indent = indent; }
	
	//关于 布局padding -- 实际上就是在 左右的控制空格（padding即内边距）
	const char *GetContainerPadding () { return containerPadding; }
	void SetContainerPadding (const char *padding) { containerPadding = padding; }
	const char *GetKeyPaddingLeft () { return keyPaddingLeft; }
	void SetKeyPaddingLeft (const char *padding) { keyPaddingLeft = padding; }
	const char *GetKeyPaddingRight () { return keyPaddingRight; }
	void SetKeyPaddingRight (const char *padding) { keyPaddingRight = padding; }
	
	//关于 布局样式
	ContainerLayout GetDefaultContainerLayout () { return defaultContainerLayout; }
    void SetDefaultContainerLayout (ContainerLayout layout) { defaultContainerLayout = layout; }

	//关于 强制默认设定
    bool GetForceDefaultContainerLayout () { return forceDefaultContainerLayout; }
    void SetForceDefaultContainerLayout (bool force) { forceDefaultContainerLayout = force; }

	//关于 输出对象/位置
	std::ostream *GetWriter () { return writer; }
    void SetWriter (std::ostream *writer) { this->writer = writer; }

	//本程序是 重构json对象的输出 -- 如果没有指定文件，输出到标准屏幕；否则，输出到文件
	std::ostream& Write()
	{
		if(writer == NULL)
			return std::cout;
		return *writer;
	}

	//声明 重载的+多样的 核心函数， ！！头文件中声明，源文件中实现！！
	void WriteEscapedChar (char c);
    void WriteString (const char *str);

    void StartChild (bool isKey);
    void StartChild () { StartChild (false); }

    void StartContainer (ContainerType type, ContainerLayout layout);
    void EndContainer ();

    void StartArray () { StartContainer (CONTAINER_TYPE_ARRAY, CONTAINER_LAYOUT_INHERIT); }
    void StartArray (ContainerLayout layout) { StartContainer (CONTAINER_TYPE_ARRAY, layout); }
    void StartShortArray () { StartContainer (CONTAINER_TYPE_ARRAY, CONTAINER_LAYOUT_SINGLE_LINE); }
    void EndArray () { EndContainer (); }

    void StartObject () { StartContainer (CONTAINER_TYPE_OBJECT, CONTAINER_LAYOUT_INHERIT); }
    void StartObject (ContainerLayout layout) { StartContainer (CONTAINER_TYPE_OBJECT, layout); }
    void StartShortObject () { StartContainer (CONTAINER_TYPE_OBJECT, CONTAINER_LAYOUT_SINGLE_LINE); }
    void EndObject () { EndContainer (); }

    void Key (const char *key);

    void NullValue ();
	//重载 遇到这些 非数值的 -- string char* bool 
	//因内部操作不同泛型解决不了，可以利用重载
    void Value (const char *value);
    void Value (std::string value);
	void Value (bool value);

	//定义泛型 -- 保证Value函数可以读入 不只是 int的值，节省的代码量
	#define VALUE_DEF(t)  void Value(t value) { StartChild(); Write() << value; }
	
	VALUE_DEF(signed char)		//VALUE_DEF(int8_t)
    VALUE_DEF(unsigned char)	//VALUE_DEF(uint8_t)
    VALUE_DEF(short)			//VALUE_DEF(int16_t)
    VALUE_DEF(unsigned)			//VALUE_DEF(uint16_t)
    VALUE_DEF(int)				//VALUE_DEF(int32_t)
    //VALUE_DEF(unsigned int)		//VALUE_DEF(uint32_t)
    VALUE_DEF(long long)		//VALUE_DEF(int64_t)
    VALUE_DEF(unsigned long long)//VALUE_DEF(uint64_t)
    VALUE_DEF(float)
    VALUE_DEF(double)

	#define KEYVALUE_DEF(t) void KeyValue(const char *key,t value) { Key(key); Value(value);}
    void KeyNullValue (const char *key) { Key (key); NullValue (); }

	KEYVALUE_DEF(const char *)
    KEYVALUE_DEF(std::string)
    KEYVALUE_DEF(bool)
	KEYVALUE_DEF(signed char)		//KEYVALUE_DEF(int8_t)
    KEYVALUE_DEF(unsigned char)		//KEYVALUE_DEF(uint8_t)
    KEYVALUE_DEF(short)				//KEYVALUE_DEF(int16_t)
    KEYVALUE_DEF(unsigned)			//KEYVALUE_DEF(uint16_t)
    KEYVALUE_DEF(int)				//KEYVALUE_DEF(int32_t)
    //KEYVALUE_DEF(unsigned int)		//KEYVALUE_DEF(uint32_t)
    KEYVALUE_DEF(long long)			//KEYVALUE_DEF(int64_t)
    KEYVALUE_DEF(unsigned long long)//KEYVALUE_DEF(uint64_t)
    KEYVALUE_DEF(float)
    KEYVALUE_DEF(double)

private:
	//所有的变量 进行底层封装，留的接口都是操作 -- 面向对象的思想
    std::ostream *writer;
    int initialIndentDepth;
    const char *indent;
    const char *containerPadding;
    const char *keyPaddingLeft;
    const char *keyPaddingRight;
    ContainerLayout defaultContainerLayout;
    bool forceDefaultContainerLayout;

	struct Container
	{
		ContainerType type;
		ContainerLayout layout;
		bool isKey;		//isKey用来判断是键还是值，由于布局/符号不同，所以我们区别对待
		int childCount;

		//构造函数
		Container(ContainerType type,ContainerLayout layout):
		type(type),layout(layout),isKey(false),childCount(0){}
	};

	std::stack<Container *> depth;
	void Indent();	
};
#endif /*_JSONWRITER_H*/

