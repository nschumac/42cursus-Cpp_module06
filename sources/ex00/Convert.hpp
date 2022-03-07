#ifndef CONVERT_H
# define CONVERT_H

#include <iostream>
#include <string>

#define CHAR_MASK (1 << 0)
#define INT_MASK (1 << 1)
#define FLOAT_MASK (1 << 2)
#define DOUBLE_MASK (1 << 3)

class Convert
{
private:

	
	std::string	_input;
	int			_iFlags;
	char		_cData;
	int			_iData;
	float		_fData;
	double		_dData;

	Convert();

	void	getType();
	void	setData();
public:
	Convert(std::string	input) : _input(input), _iFlags(0), _cData(0), _iData(0), _fData(0.0f), _dData(0.0){ setData();};
	Convert(Convert const &in);
	Convert &operator=(Convert const & in);
	~Convert();
	void	print();
};

#endif