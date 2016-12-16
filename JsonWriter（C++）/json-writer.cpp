#include "json-writer.h"
using namespace std;

//结合缩进来提升可读性 stack -- 同一深度缩进相同的空格
void JsonWriter::Indent()
{
	for(int i=0,s=initialIndentDepth+depth.size();i<s;i++)
		Write() << indent;
}

//元素的开始和结束都需要函数来操作，分别为StartContainer 和 EndContainer,Container是指对象或者数组
void JsonWriter::StartContainer(ContainerType type,ContainerLayout layout)
{
	if(forceDefaultContainerLayout)
		layout = defaultContainerLayout;
	else if(layout == CONTAINER_LAYOUT_INHERIT)
	{
		if(depth.size() > 0)
			layout = depth.top() ->layout;
		else
			layout = defaultContainerLayout;
	}

	StartChild();
	depth.push(new Container(type,layout));
	Write() << (type == CONTAINER_TYPE_OBJECT ? '{' : '[');
}

void JsonWriter::EndContainer()
{
	Container *container = depth.top();
	depth.pop();
	if(container->childCount > 0)
	{
		if(container->layout == CONTAINER_LAYOUT_MULTI_LINE)
		{
			Write() << endl;
			Indent();
		}
		else
			Write() << containerPadding;
	}
	Write() << (container->type == CONTAINER_TYPE_OBJECT ? '}' : ']');
	delete container;
}

//容器中需要一个开始标识和结束标识，用来规定执行的流程
//StartChild主要针对 对象 + 元素 + 键值 的缩进和标点符号 问题
void JsonWriter::StartChild(bool isKey)
{
	//如果深度为0，说明是根节点，只用考虑缩进就好
	if(depth.size() == 0)
	{
		if(initialIndentDepth >0)
			Indent();
		return ;
	}

	//如果是子节点，需要区分类型
	Container *container = depth.top();
	//针对数组中的元素（都是数值） 或者 是对象中的值 ，连着输出一个‘，’，用来区分值
	if(container->childCount >0 && (container->type == CONTAINER_TYPE_ARRAY || (container->type == CONTAINER_TYPE_OBJECT && !container->isKey)))
	{
		Write() << ",";
		//单行布局 与 多行布局的区别在于换行和缩进
		if(container->layout == CONTAINER_LAYOUT_SINGLE_LINE)
			Write() << containerPadding;
		else
		{
			Write() << endl;
			Indent();
		}
	}
	else if(container->childCount == 0)
	{
		Write() << containerPadding;
		if(container->layout == CONTAINER_LAYOUT_MULTI_LINE)
		{
			Write() << endl;
			Indent();
		}
	}

	container->isKey = isKey;
	container->childCount++;
}

//当添加字符串时，输出时没有双引号，不符合标准，所以需要手动处理（不同于上面的数值类 元素）
void JsonWriter::WriteString(const char *str)
{
	Write() << "\"";
	for(int i=0;str[i]!=0;i++)
		WriteEscapedChar(str[i]);
	Write() << "\"";
}

//处理转义字符,每个字符 用字符串输出
void JsonWriter::WriteEscapedChar(char c)
{
	switch(c)
	{
		case '"'	:Write() << "\\\""; break;
		case '\\'	:Write() << "\\\\"; break;
		case '\b'	:Write() << "\\b" ; break;
		case '\f'	:Write() << "\\f" ; break;
		case '\n'	:Write() << "\\n" ; break;
		case '\r'	:Write() << "\\r" ; break;
		case '\t'	:Write() << "\\t" ; break;
		default		:Write() << c;		break;
	}
}

//上一节使用的value()函数 以及key() NullValue()
void JsonWriter::Value(const char* value)
{
	StartChild();
	WriteString(value);
}

void JsonWriter::Value(string value)
{
	StartChild();
	WriteString(value.c_str());
}

void JsonWriter::Value(bool value)
{
	StartChild();
	Write() << (value ? "true" : "false");
}

void JsonWriter::Key(const char *key)
{
	StartChild(true);
	WriteString(key);
	Write() << keyPaddingLeft << "." << keyPaddingRight;
}

void JsonWriter::NullValue()
{
	StartChild();
	Write() << "null";
}