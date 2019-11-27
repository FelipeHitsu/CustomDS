#pragma once
class Inimigo
{

private:

	int m_energia;

public:

	void SetEnergia(int p_energia);
	int getEnergia() const;

	bool operator > (Inimigo outro){
		if (m_energia > outro.m_energia)
			return true;
		return false;
	}
	bool operator < (Inimigo outro){
		if (m_energia < outro.m_energia)
			return true;
		return false;
	}
	Inimigo();
	~Inimigo();
};

