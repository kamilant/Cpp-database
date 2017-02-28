#ifndef DMETHODS_H
#define DMETHODS_H
using namespace std;
  class DMethods {
      string methodName, physicalP, depictedFeature, imageType;
    public:
        DMethods (
          string _name="",
          string _physical="",
          string _depictedFeature="",
          string _imageType ="");

        DMethods(const DMethods &method);
        //destructor for all the child classes
        virtual ~DMethods();
        //SETTERS
        void setMethodName(string _methodName);
        void setPhysicalPhenomena(string _physicalPhenomena);
        void setDepictedFeature(string _depictedFeature);
        void setImageType(string _imageType);
        //GETTERS
        string getMethodName();
        string getPhysicalPhenomena();
        string getDepictedFeature();
        string getImageType();
        vector<string> getProperties();
        // METHODS

        void saveMethod(DMethods &method);
  };
#endif
