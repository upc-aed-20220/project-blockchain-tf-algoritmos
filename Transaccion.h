#include <iostream>
#include <string>

using namespace std;

class Transaccion
{
private:
    struct Fecha
    {
        int dia;
        int mes;
        int anio;

        Fecha()
        {
            this->dia = 1;
            this->mes = 1;
            this->anio = 1900;
        }

        Fecha(int dia, int mes, int anio)
        {
            this->dia = dia;
            this->mes = mes;
            this->anio = anio;
        }

        bool operator==(Fecha f)
        {
            return dia == f.dia && f.mes == mes && f.anio == anio;
        }
        bool operator<(Fecha f)
        {
            return (anio < f.anio) ? true : (anio == f.anio && mes < f.mes)               ? true
                                        : (anio == f.anio && mes == f.mes && dia < f.dia) ? true
                                                                                          : false;
        }
        string getStringFecha()
        {
            string output = "\t";
            output.append(to_string(dia));
            output.append("-");
            output.append(to_string(mes));
            output.append("-");
            output.append(to_string(anio));
            return output;
        }
    };

    string emisor;
    string receptor;
    float monto;
    Fecha fecha;

public:
    Transaccion()
    {
        emisor = "";
        receptor = "";
        monto = 0.0;
        this->fecha.dia = 1;
        this->fecha.mes = 1;
        this->fecha.anio = 1900;
    }

    Transaccion(int dia, int mes, int anio)
    {
        emisor = "";
        receptor = "";
        monto = 0.0;
        this->fecha.dia = dia;
        this->fecha.mes = mes;
        this->fecha.anio = anio;
    }

    Transaccion(string _emisor, string _receptor, float _monto, int dia, int mes, int anio)
    {
        emisor = _emisor;
        receptor = _receptor;
        monto = _monto;
        this->fecha.dia = dia;
        this->fecha.mes = mes;
        this->fecha.anio = anio;
    }

    bool operator<=(Transaccion t)
    {
        if (this->getAnio() < t.getAnio())
        {
            return true;
        }
        else
        {
            return (this->getFechaEnSegundos() <= t.getFechaEnSegundos()) ? true : false;
        }
    }

    bool operator<(Transaccion t)
    {
        return this->fecha < t.fecha;
    }

    bool operator>(Transaccion t)
    {
        if (this->getAnio() > t.getAnio())
        {
            return true;
        }
        else
        {
            return (this->getFechaEnSegundos() > t.getFechaEnSegundos()) ? true : false;
        }
    }
    bool operator==(Transaccion t)
    {
        if (this->getAnio() == t.getAnio())
        {
            if (this->getFechaEnSegundos() == t.getFechaEnSegundos())
            {
                return true;
            }
            else
                return false;
        }
        else
        {
            return false;
        }
    }

    string getString()
    {
        string output = "";
        output.append(to_string(monto));
        output.append("\t");
        output.append(emisor);
        output.append("\t");
        output.append(receptor);
        output.append("    ");
        output.append(fecha.getStringFecha());
        output.append("\n");
        return output;
    }

    string getFormatoGuardar()
    {
        string output = "";
        output.append(to_string(monto));
        output.append(",");
        output.append(emisor);
        output.append(",");
        output.append(receptor);
        output.append(",");
        output.append(to_string(this->fecha.dia));
        output.append(to_string(this->fecha.mes));
        output.append(to_string(this->fecha.anio));
        output.append("\n");
        return output;
    }

    string show()
    {
        return getEmisor() + " - " + std::to_string(getMonto()) + " - " + getReceptor() + " => " + fecha.getStringFecha();
    }

    string getEmisor() { return emisor; }
    string getReceptor() { return receptor; }
    float getMonto() { return monto; }
    int getAnio() { return fecha.anio; }

    size_t getFechaEnSegundos()
    {
        size_t segundosFecha = 0;
        segundosFecha += (this->fecha.dia * 86400);   
        segundosFecha += (this->fecha.mes * 2592000); 
        return segundosFecha;
    }
};
