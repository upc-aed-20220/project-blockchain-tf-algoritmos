#include <iostream>
#include <string>

using namespace std;

class Transaccion
{
private:
    string emisor;
    string receptor;
    float monto;
public:
    Transaccion() {
        emisor = "";
        receptor = "";
        monto = 0.0;
    }

    Transaccion(string _emisor, string _receptor, float _monto)
    {
        emisor = _emisor;
        receptor = _receptor;
        monto = _monto;
    }
    string getString() {
        string output = "";
        output.append(to_string(monto));
        output.append("\t");
        output.append(emisor);
        output.append("\t");
        output.append(receptor);
        return output;
    }
    string getEmisor() { return emisor; }
    string getReceptor() { return receptor; }
    float getMonto() { return monto; }
};

/*ostream& operator<<(ostream& o, const Transaccion<float>& p)
{
    o << "(" << p.monto << " -> " << p.emisor << " -> " << p.receptor << ")";
    return o;
}*s/
