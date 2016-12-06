#include <iostream>


class STRING_BUFFER 
{
public:
	char* stringbuff;                                   
	int stringlength;                                       


public:
	int ref_count;
	int *ptrCount;

	STRING_BUFFER();  
	STRING_BUFFER(char*, int);   
	char charAt(int) const;   
	int length() const;                            
	void reserve(int);                             
	void append(char);                          
	STRING_BUFFER* STRING_BUFFER::smartCopy(char*, int);
	void print() 
	{  
		for (int i = 0; i < stringlength; i++) 
		{
			std::cout << stringbuff[i];
		}
		std::cout << std::endl;
		std::cout << "Length: " << stringlength << std::endl;
	}

	STRING_BUFFER& operator=(STRING_BUFFER&b)
	
	{
		this->stringbuff = b.stringbuff;
		this->stringlength = b.stringlength;
		this->ref_count = b.ref_count;

		ptrCount = (int*)(&b.ref_count);
		*ptrCount = *ptrCount + 1;

		this->ref_count = *ptrCount;
	}
	
	STRING_BUFFER( const STRING_BUFFER&b)
	{
		this->stringbuff = b.stringbuff;
		this->stringlength = b.stringlength;
		this->ref_count = b.ref_count;
		ptrCount = (int*)(&b.ref_count);
		*ptrCount = *ptrCount + 1;
		this->ref_count = *ptrCount;
	}

	STRING_BUFFER::~STRING_BUFFER() 
	{ 
		//destructor for allocated buffer
		if (*this->ptrCount == 1){

			delete[] this->stringbuff;
		}
		else
		{
			--(*this->ptrCount);
		}
	}
};

STRING_BUFFER::STRING_BUFFER() 
{
	stringbuff = new char();
	stringlength = 0;
	ref_count = 1;
	ptrCount = &ref_count;
}

STRING_BUFFER::STRING_BUFFER(char* newString, int length) 
{    
	this->stringbuff = newString;
	this->stringlength = length;
	this->ref_count = 1;
}

char STRING_BUFFER::charAt(int index) const 
{	//returns the character at the passed index
	if (stringlength == 0 || index >= stringlength || index < 0) 
	{
		std::cout << "Invalid index accessed." << std::endl;
		return ' ';
	}
	else
		return stringbuff[index];

}

int STRING_BUFFER::length() const 
{   
	//returns the length of the buffer
	return stringlength;
}

void STRING_BUFFER::reserve(int length) 
{ 
	//allocates memory for the string, according to the passed character length
	char* mystring = new char[length];

	delete[] stringbuff;
	stringbuff = new char[length];
	stringlength = length;
	for (int i = 0; i < stringlength; i++)
	{
		stringbuff[i] = mystring[i];
	}
	delete[] mystring;

}
STRING_BUFFER* STRING_BUFFER::smartCopy(char* newString, int length) 
{
	STRING_BUFFER *temp = new STRING_BUFFER();
	temp->stringlength = length;
	int it = 0;
	temp->reserve(length);
	for (int i = 0; i < temp->stringlength; i++)
	{
		temp->stringbuff[i] = newString[i];
	}
	temp->ref_count = 1;
	return temp;
}
void STRING_BUFFER::append(char newChar) 
{	
	//appends a single character at the end
	if (*this->ptrCount > 1)
	{
		STRING_BUFFER *temp = smartCopy(this->stringbuff, this->stringlength);

		char* mystring = new char[temp->stringlength + 1];
		for (int i = 0; i < temp->stringlength; i++)
		{
			mystring[i] = temp->stringbuff[i];
		}
		--(*this->ptrCount);
		mystring[temp->stringlength] = newChar;
		delete[] temp->stringbuff;
		temp->stringbuff = new char[temp->stringlength + 1];
		temp->stringlength++;
		for (int i = 0; i < temp->stringlength; i++)
		{
			temp->stringbuff[i] = mystring[i];
		}
		delete[] mystring;
		this->stringbuff = temp->stringbuff;
		this->stringlength = temp->stringlength;
		this->ptrCount = temp->ptrCount;

	}
	else
	{
		char* mystring = new char[stringlength + 1];
		for (int i = 0; i < stringlength; i++)
		{
			mystring[i] = stringbuff[i];
		}
		mystring[stringlength] = newChar;
		delete[] stringbuff;
		stringbuff = new char[stringlength + 1];
		stringlength++;
		for (int i = 0; i < stringlength; i++)
		{
			stringbuff[i] = mystring[i];
		}
		delete[] mystring;
	}

}

int main(void) 
{

	STRING_BUFFER *newString = new STRING_BUFFER();
	newString->print();
	std::cout << "Appending 'c'..." << std::endl;
	newString->append('c');
	newString->print();
	newString->append('f');
	newString->print();
	newString->append('g');
	newString->print();
	newString->append('h');
	newString->print();
	newString->append('i');
	newString->print();
	std::cout << std::endl;

	newString->print();
	STRING_BUFFER *b = new STRING_BUFFER(*newString);
	STRING_BUFFER *c = new STRING_BUFFER(*newString);

	newString->print();
	c->print();
	c->append('j');

	c->print();


	b->print();
	b->append('k');

	b->print();

	newString->print();

	delete b;
	delete newString;

}
