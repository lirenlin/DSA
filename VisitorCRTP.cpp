#include "iostream"
#include <vector>

//forward declarations
class Boat;
class Plane;

//create our visitor base class
class VisitorBase
{
public:
  virtual void visit(const Boat& b) = 0;
  virtual void visit(const Plane& p) = 0;
};

//write our accept method in the base class
//this is helpful because it allows us to have containers of Visitable objects
class Visitable
{
public:
  virtual void accept(VisitorBase &v) const = 0;
};


// create the base craft class which will have our only implementation of
// the accept() method
template <typename T>
class Craft : public Visitable
{
  unsigned int size, weight, RGBAColor;

public:
  void accept(VisitorBase &v) const
    {
      const T* upcast = dynamic_cast<const T* const>(this);
      if(upcast != NULL)
	v.visit(*upcast);
    }
};

class Plane : public Craft<Plane>
{
public:
  Plane(int numberOfPassengers, int numberOfParachutes):
    numberOfPassengers(numberOfPassengers), numberOfParachutes(numberOfParachutes){};
  int numberOfPassengers, numberOfParachutes;
};

class Boat : public Craft<Boat>
{
public:
  Boat(int numberOfLifeVests, int maxNumberOfPassengers):
    numberOfLifeVests(numberOfLifeVests), maxNumberOfPassengers(maxNumberOfPassengers){};
  int numberOfLifeVests, maxNumberOfPassengers;
};


//subclass the visitor base class with some implementations
class CraftSafetyComplianceVisitor: public VisitorBase
{
public:
  CraftSafetyComplianceVisitor ():compliant(true){};

  virtual void visit(const Boat& boat)
    {
      compliant &= boat.numberOfLifeVests >= boat.maxNumberOfPassengers;
    };

  virtual void visit(const Plane& plane)
    {
      compliant &= plane.numberOfParachutes >= plane.numberOfPassengers;
    };
  bool compliant;
};


int main(int argc, char* argv[])
{
  std::vector<Visitable*> crafts;
  crafts.push_back(new Boat(1,1));
  crafts.push_back(new Plane(1,1));

  CraftSafetyComplianceVisitor  v;
  for(std::vector<Visitable*>::iterator i = crafts.begin();
      i != crafts.end(); i++)
    {
      (*i)->accept(v);
    }

  std::cout << (!v.compliant ? "not " : "") << "all crafts are in compliance"
    << std::endl;

  return 0;
}
