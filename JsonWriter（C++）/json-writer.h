#ifndef _JSONWRITER_H
#define _JSONWRITER_H
#include <iostream>
#include <string>
#include <stack>

class JsonWriter
{
public:
	//json����Ҫ���������� -- array + object
	enum ContainerType
	{
		CONTAINER_TYPE_ARRAY,
		CONTAINER_TYPE_OBJECT
	};

	//json�Ĳ��� -- �̳и��� + ����Ԫ�� + ����Ԫ��
	enum ContainerLayout
	{
		CONTAINER_LAYOUT_INHERIT,
		CONTAINER_LAYOUT_MULTI_LINE,
		CONTAINER_LAYOUT_SINGLE_LINE
	};

	//��ȷ�ģ������� -- ������ ��ʽת��ʱ ʹ�øù��캯��
	//c++11 ���е� ���캯������
	explicit JsonWriter():      
        writer (NULL),
        initialIndentDepth (0),
        indent ("  "),
        containerPadding (" "),
        keyPaddingLeft (""),
        keyPaddingRight (" "),
        defaultContainerLayout (CONTAINER_LAYOUT_MULTI_LINE),
        forceDefaultContainerLayout (false) { }

	//�����Ҫ ѹ�� �����json���� -- ���ٿո� + ���ٻ���
	void ConfigureCompressedOutput()
	{
		SetIndent("");
		SetContainerPadding("");
		SetKeyPaddingLeft("");
		SetKeyPaddingRight("");
		SetDefaultContainerLayout(CONTAINER_LAYOUT_SINGLE_LINE);
		SetForceDefaultContainerLayout(true);
	}

	//���� ����
	int GetInitialIndentDepth () { return initialIndentDepth; }
	void SetInitialIndentDepth(int depth) { initialIndentDepth = depth; }
	const char *GetIndent() { return indent; }
	void SetIndent(const char *indent) { this->indent = indent; }
	
	//���� ����padding -- ʵ���Ͼ����� ���ҵĿ��ƿո�padding���ڱ߾ࣩ
	const char *GetContainerPadding () { return containerPadding; }
	void SetContainerPadding (const char *padding) { containerPadding = padding; }
	const char *GetKeyPaddingLeft () { return keyPaddingLeft; }
	void SetKeyPaddingLeft (const char *padding) { keyPaddingLeft = padding; }
	const char *GetKeyPaddingRight () { return keyPaddingRight; }
	void SetKeyPaddingRight (const char *padding) { keyPaddingRight = padding; }
	
	//���� ������ʽ
	ContainerLayout GetDefaultContainerLayout () { return defaultContainerLayout; }
    void SetDefaultContainerLayout (ContainerLayout layout) { defaultContainerLayout = layout; }

	//���� ǿ��Ĭ���趨
    bool GetForceDefaultContainerLayout () { return forceDefaultContainerLayout; }
    void SetForceDefaultContainerLayout (bool force) { forceDefaultContainerLayout = force; }

	//���� �������/λ��
	std::ostream *GetWriter () { return writer; }
    void SetWriter (std::ostream *writer) { this->writer = writer; }

	//�������� �ع�json�������� -- ���û��ָ���ļ����������׼��Ļ������������ļ�
	std::ostream& Write()
	{
		if(writer == NULL)
			return std::cout;
		return *writer;
	}

	//���� ���ص�+������ ���ĺ����� ����ͷ�ļ���������Դ�ļ���ʵ�֣���
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
	//���� ������Щ ����ֵ�� -- string char* bool 
	//���ڲ�������ͬ���ͽ�����ˣ�������������
    void Value (const char *value);
    void Value (std::string value);
	void Value (bool value);

	//���巺�� -- ��֤Value�������Զ��� ��ֻ�� int��ֵ����ʡ�Ĵ�����
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
	//���еı��� ���еײ��װ�����Ľӿڶ��ǲ��� -- ��������˼��
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
		bool isKey;		//isKey�����ж��Ǽ�����ֵ�����ڲ���/���Ų�ͬ��������������Դ�
		int childCount;

		//���캯��
		Container(ContainerType type,ContainerLayout layout):
		type(type),layout(layout),isKey(false),childCount(0){}
	};

	std::stack<Container *> depth;
	void Indent();	
};
#endif /*_JSONWRITER_H*/

