#include <iostream>


	class STRING_BUFFER 
	{
	public:
		char* stringbuff;                                   
		int stringlength;                                   
	public:
		STRING_BUFFER();								
		~STRING_BUFFER();								
														
		STRING_BUFFER(char*, int);						
		char charAt(int) const;							
		int length() const;                            
		void reserve(int);                             
		void append(char);                          

		void print() { 

			for (int i = 0; i < stringlength; i++) {
				std::cout << stringbuff[i];
			}
			std::cout << std::endl;
			std::cout << "Length: " << stringlength << std::endl;
		}

	};

STRING_BUFFER::~STRING_BUFFER() 
{ 
	//destructor calling
	delete[] stringbuff;

}

STRING_BUFFER::STRING_BUFFER() 
{
	stringbuff = new char();
	stringlength = 0;
}

STRING_BUFFER::STRING_BUFFER(char* newString, int length) 
{ 
	//constructor to convert a char* to STRING_BUFFER
	stringbuff = newString;
	stringlength = length;
}

char STRING_BUFFER::charAt(int index) const 
{ 
	//returns the character at the passed index
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

void STRING_BUFFER::append(char newChar) 
{ 
	//appends a single character at the end
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
	std::cout << newString->charAt(0) << std::endl;
	std::cout << newString->charAt(1) << std::endl;
	std::cout << newString->charAt(2) << std::endl;
	std::cout << newString->charAt(3) << std::endl;
	std::cout << newString->charAt(4) << std::endl;
	std::cout << newString->charAt(5) << std::endl;


	std::cout << newString->stringlength << std::endl;
	newString->reserve(10);
	std::cout << newString->stringlength << std::endl;


}
