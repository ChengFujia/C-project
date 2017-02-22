#include "json-writer.h"
using namespace std;

// 用c++编写一个json生成器
//½áºÏËõ½øÀ´ÌáÉý¿É¶ÁÐÔ stack -- Í¬Ò»Éî¶ÈËõ½øÏàÍ¬µÄ¿Õ¸ñ
void JsonWriter::Indent()
{
	//Ã¿Ò»²ãÊÇÁ½¸ö¿Õ¸ñµÄËõ½ø
	for(int i=0,s=initialIndentDepth+depth.size();i<s;i++)
		Write() << indent;
}

//ÔªËØµÄ¿ªÊ¼ºÍ½áÊø¶¼ÐèÒªº¯ÊýÀ´²Ù×÷£¬·Ö±ðÎªStartContainer ºÍ EndContainer,ContainerÊÇÖ¸¶ÔÏó»òÕßÊý×é
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
	//ÐÂ½¨Ò»¸öContainer
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

//ÈÝÆ÷ÖÐÐèÒªÒ»¸ö¿ªÊ¼±êÊ¶ºÍ½áÊø±êÊ¶£¬ÓÃÀ´¹æ¶¨Ö´ÐÐµÄÁ÷³Ì
//StartChildÖ÷ÒªÕë¶Ô ¶ÔÏó + ÔªËØ + ¼üÖµ µÄËõ½øºÍ±êµã·ûºÅ ÎÊÌâ
void JsonWriter::StartChild(bool isKey)
{
	//Èç¹ûÉî¶ÈÎª0£¬ËµÃ÷ÊÇ¸ù½Úµã£¬Ö»ÓÃ¿¼ÂÇËõ½ø¾ÍºÃ
	if(depth.size() == 0)
	{
		if(initialIndentDepth >0)
			Indent();
		return ;
	}

	//Èç¹ûÊÇ×Ó½Úµã£¬ÐèÒªÇø·ÖÀàÐÍ
	Container *container = depth.top();
	//Õë¶ÔÊý×éÖÐµÄÔªËØ£¨¶¼ÊÇÊýÖµ£© »òÕß ÊÇ¶ÔÏóÖÐµÄÖµ £¬Á¬×ÅÊä³öÒ»¸ö¡®£¬¡¯£¬ÓÃÀ´Çø·ÖÖµ
	if(container->childCount >0 && (container->type == CONTAINER_TYPE_ARRAY || (container->type == CONTAINER_TYPE_OBJECT && !container->isKey)))
	{
		Write() << ",";
		//µ¥ÐÐ²¼¾Ö Óë ¶àÐÐ²¼¾ÖµÄÇø±ðÔÚÓÚ»»ÐÐºÍËõ½ø
		if(container->layout == CONTAINER_LAYOUT_SINGLE_LINE)
			Write() << containerPadding;
		else
		{
			Write() << endl;
			Indent();
		}
	}
	//Èç¹ûÃ»ÔªËØ£¬Á¬¼ä¸ô·ûºÅ¶¼ÄÜÊ¡È¥
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

//µ±Ìí¼Ó×Ö·û´®Ê±£¬Êä³öÊ±Ã»ÓÐË«ÒýºÅ£¬²»·ûºÏ±ê×¼£¬ËùÒÔÐèÒªÊÖ¶¯´¦Àí£¨²»Í¬ÓÚÉÏÃæµÄÊýÖµÀà ÔªËØ£©
void JsonWriter::WriteString(const char *str)
{
	Write() << "\"";
	for(int i=0;str[i]!=0;i++)
		WriteEscapedChar(str[i]);
	Write() << "\"";
}

//´¦Àí×ªÒå×Ö·û,Ã¿¸ö×Ö·û ÓÃ×Ö·û´®Êä³ö
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

//ÉÏÒ»½ÚÊ¹ÓÃµÄvalue()º¯Êý ÒÔ¼°key() NullValue()
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