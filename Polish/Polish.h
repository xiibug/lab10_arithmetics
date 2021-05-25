#pragma once
#ifndef _POLISH_
#define _POLISH_

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<fstream>
#include"Stack.h"

using namespace std;

class IOper
{
protected:

public:
	virtual int Priority() = 0;
	virtual int GetNumber() = 0;
	virtual IOper* Calc(IOper* a, IOper* b) = 0;
};

class TNum : public IOper
{
protected:
	int data;
public:
	TNum(int _d);
	TNum(TNum& _v);
	TNum(char* s);

	virtual int Priority();
	virtual int GetNumber();
	virtual IOper* Calc(IOper* a, IOper* b);

};

class TOper : public IOper
{
protected:
	char data;
public:
	TOper(char _d);
	TOper(TOper& _v);

	virtual int GetNumber();
};

class TPlus : public TOper
{
protected:

public:

	TPlus(char _d) : TOper(_d)
	{
	}

	virtual int Priority();
	virtual IOper* Calc(IOper* a, IOper* b);
};

class TMinus : public TOper
{
protected:

public:

	TMinus(char _d) : TOper(_d)
	{
	}

	virtual int Priority();
	virtual IOper* Calc(IOper* a, IOper* b);
};

class TMultiply : public TOper
{
protected:

public:
	TMultiply(char _d) : TOper(_d)
	{
	}

	virtual int Priority();
	virtual IOper* Calc(IOper* a, IOper* b);
};

class TDivide : public TOper
{
protected:

public:
	TDivide(char _d) : TOper(_d)
	{
	}
	virtual int Priority();
	virtual IOper* Calc(IOper* a, IOper* b);
};

class TOpenBracket : public TOper
{
protected:

public:
	TOpenBracket(char _d) : TOper(_d)
	{
	}

	virtual int Priority();
	virtual IOper* Calc(IOper* a, IOper* b);
};

class TCloseBracket : public TOper
{
protected:

public:

	TCloseBracket(char _d) : TOper(_d)
	{
	}
	virtual int Priority();

	virtual IOper* Calc(IOper* a, IOper* b);
};

class TOperFactory
{
public:
	static void Create(char* s, int& n, IOper**& opers);
};

class TPolish
{
public:
	static int Calculation(char* s);
};
int TPolish::Calculation(char* s)
{
	int n = 0;
	IOper** opers = 0;
	TOperFactory::Create(s, n, opers);
	int l = strlen(s);
	IOper** res = new IOper * [l];

	int j = 0;

	for (int i = 0; i < n; i++)
	{
		if (opers[i]->Priority() == 1)
		{
			res[j] = opers[i];
			j++;
		}
		else if (opers[i]->Priority() == -1)
		{
			res[j] = opers[i];
			j++;
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (opers[i]->Priority() == 3)
		{
			res[j] = opers[i];
			j++;
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (opers[i]->Priority() == 2)
		{
			res[j] = opers[i];
			j++;
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (opers[i]->Priority() == 0)
		{
			res[j] = opers[i];
			j++;
		}
	}

	TStack<IOper*> ns(n);

	for (int i = 0; i < j; i++)
	{
		if (res[i]->Priority() == -1)
		{
			ns.Push(res[i]);
		}
		else
		{
			IOper* b = ns.Get();
			IOper* a = ns.Get();
			IOper* c = res[i]->Calc(a, b);
			ns.Push(c);
		}
	}
	IOper* r = ns.Get();

	return r->GetNumber();
}

void TOperFactory::Create(char* s, int& n, IOper**& opers)
{
	int l = strlen(s);
	for (int i = 0; i < l; i++)
	{
		if (isdigit(s[i]) == 0)
		{
			n++;
		}
	}
	n++;
	n = 2 * n - 1;

	IOper** res = new IOper * [n];
	int start = 0;
	int j = 0;

	for (int i = 0; i < l; i++)
	{
		if (s[i] == '(')
		{
			res[j] = new TOpenBracket('(');
			j++;
		}
		else if (s[i] == ')')
		{
			res[j] = new TCloseBracket(')');
			j++;
		}
		else if (s[i] == '+')
		{
			res[j] = new TPlus('+');
			j++;
		}
		else if (s[i] == '-')
		{
			res[j] = new TMinus('-');
			j++;
		}
		else if (s[i] == '*')
		{
			res[j] = new TMultiply('*');
			j++;
		}
		else if (s[i] == '/')
		{
			res[j] = new TDivide('/');
			j++;
		}

	}

	for (int i = 0; i < l; i++)
	{
		if (isdigit(s[i]) != 0)
		{
			res[j] = new TNum(s[i] - 48);
			j++;
		}
	}

	opers = new IOper * [j];
	for (int i = 0; i < j; i++)
	{
		opers[i] = res[i];
	}
	delete[] res;
}

int TCloseBracket::Priority()
{
	return 0;
}

IOper* TCloseBracket::Calc(IOper* a, IOper* b)
{
	throw new exception;
}

int TOpenBracket::Priority()
{
	return 1;
}

IOper* TOpenBracket::Calc(IOper* a, IOper* b)
{
	throw new exception;
}

int TDivide::Priority()
{
	return 3;
}

IOper* TDivide::Calc(IOper* a, IOper* b)
{
	if (b->GetNumber() == 0)
		throw new exception;
	TNum* res = new TNum(a->GetNumber() / b->GetNumber());
	return res;
}

int TMultiply::Priority()
{
	return 3;
}

IOper* TMultiply::Calc(IOper* a, IOper* b)
{
	TNum* res = new TNum(a->GetNumber() * b->GetNumber());
	return res;
}

int TMinus::Priority()
{
	return 2;
}

IOper* TMinus::Calc(IOper* a, IOper* b)
{
	TNum* res = new TNum(a->GetNumber() - b->GetNumber());
	return res;
}

int TPlus::Priority()
{
	return 2;
}

IOper* TPlus::Calc(IOper* a, IOper* b)
{
	TNum* res = new TNum(a->GetNumber() + b->GetNumber());
	return res;
}

TOper::TOper(char _d)
{
	data = _d;
}

TOper::TOper(TOper& _v)
{
	data = _v.data;
}

int TOper::GetNumber()
{
	return -1;
}

TNum::TNum(int _d)
{
	data = _d;
}

TNum::TNum(TNum& _v)
{
	data = _v.data;
}

TNum::TNum(char* s)
{
	if (strlen(s) == 0)
		throw new exception;
	data = atof(s);
}

int TNum::Priority()
{
	return -1;
}

int TNum::GetNumber()
{
	return data;
}

IOper* TNum::Calc(IOper* a, IOper* b)
{
	throw new exception;
}

#endif