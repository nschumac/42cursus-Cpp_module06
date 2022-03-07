#include "Convert.hpp"
#include <exception>
#include <sstream>
#include <cmath>

Convert::Convert() {

}
		
void	Convert::print()
{
	std::cout << "char: ";
	if (this->_iFlags & CHAR_MASK)
		std::cout << "impossible" << std::endl;
	else if (this->_cData < 32 || this->_cData > 127)
		std::cout << "non displayable" << std::endl;
	else
		std::cout << "'" << this->_cData << "'" << std::endl;
	
	std::cout << "int: ";
	if (this->_iFlags & INT_MASK)
		std::cout << "impossible" << std::endl;
	else
		std::cout << this->_iData << std::endl;
	
	std::cout << "float: ";
	if (this->_iFlags & FLOAT_MASK)
		std::cout << "impossible" << std::endl;
	else
	{
		std::stringstream ss;
		ss << this->_fData;
		std::string buf = ss.str();
		if (buf.find('.') == std::string::npos && !std::isnan(this->_fData) && !std::isinf(this->_fData))
			buf += ".0";
		std::cout << buf << "f" << std::endl;	
	}
	std::cout << "double: ";
	if (this->_iFlags & DOUBLE_MASK)
		std::cout << "impossible" << std::endl;
	else
	{
		std::stringstream ss;
		ss << this->_dData;
		std::string buf = ss.str();;
		if (buf.find('.') == std::string::npos && !std::isnan(this->_dData) && !std::isinf(this->_dData))
			buf += ".0";
		std::cout << buf << std::endl;
	}
}

void	Convert::setData()
{
	if (this->_input.length() == 3 && this->_input[0] == '\'' && this->_input[2] == '\'')
	{
		this->_cData = this->_input[1];
		this->_iData = static_cast<int>(this->_cData);
		this->_fData = static_cast<float>(this->_cData);
		this->_dData = static_cast<double>(this->_cData);
	}
	else
	{
		if (this->_input.find('f') != std::string::npos || this->_input == "nanf" || this->_input == "+inff" || this->_input == "-inff")
		{
			try
			{
				this->_fData = std::stof(_input);
			}
			catch (std::out_of_range & e)
			{
				this->_iFlags |= FLOAT_MASK;
				this->_iFlags |= INT_MASK;
				this->_iFlags |= CHAR_MASK;
				this->_iFlags |= DOUBLE_MASK;
				return ;
			}
			if (!std::isinf(this->_fData) && (this->_fData >  __DBL_MAX__ || this->_fData < (-__DBL_MAX__ -1)))
				this->_iFlags |= DOUBLE_MASK;
			else
				this->_dData = static_cast<double>(this->_fData);
			if (this->_fData > __INT_MAX__ || this->_fData < INT_MIN || std::isnan(this->_fData))
				this->_iFlags |= INT_MASK;
			else
				this->_iData = static_cast<int>(this->_fData);
			if (this->_fData > 255 || this->_fData < -256 || std::isnan(this->_fData))
				this->_iFlags |= CHAR_MASK;
			else
				this->_cData = static_cast<char>(this->_fData);
		}
		else if (this->_input.find('.') != std::string::npos || this->_input == "nan" || this->_input == "+inf" || this->_input == "-inf")
		{
			try
			{
				this->_dData = std::stod(_input);
			}
			catch (std::out_of_range & e)
			{
				this->_iFlags |= DOUBLE_MASK;
				this->_iFlags |= FLOAT_MASK;
				this->_iFlags |= INT_MASK;
				this->_iFlags |= CHAR_MASK;
				return ;
			}
			if (!std::isinf(this->_dData) && (this->_dData >  __FLT_MAX__ || this->_dData < (-__FLT_MAX__ -1)))
				this->_iFlags |= FLOAT_MASK;
			else
				this->_fData = static_cast<float>(this->_dData);
			if (this->_dData > __INT_MAX__ || this->_dData < INT_MIN || std::isnan(this->_dData))
				this->_iFlags |= INT_MASK;
			else
				this->_iData = static_cast<int>(this->_dData);
			if (this->_dData > 255 || this->_dData < -256 || std::isnan(this->_dData))
				this->_iFlags |= CHAR_MASK;
			else
				this->_cData = static_cast<char>(this->_dData);
		}
		else
		{
			try
			{
				this->_iData = std::stoi(this->_input);
			}
			catch(const std::out_of_range& e)
			{
				this->_iFlags |= INT_MASK;
				this->_iFlags |= CHAR_MASK;
				this->_iFlags |= FLOAT_MASK;
				this->_iFlags |= DOUBLE_MASK;
				return ;
			}
			
			this->_fData = static_cast<float>(this->_iData);
			this->_dData = static_cast<double>(this->_iData);
			
			if (this->_iData > 255 || this->_iData < -256 || std::isnan(this->_iData))
				this->_iFlags |= CHAR_MASK;
			else
				this->_cData = static_cast<char>(this->_iData);
		}
	}
}

Convert &Convert::operator=(Convert const & in) {
	this->_iFlags = in._iFlags;
	this->_input = in._input;
	this->_cData = in._cData;
	this->_iData = in._iData;
	this->_fData = in._fData;
	this->_dData = in._dData;
	return (*this);
}

Convert::~Convert() {

}

