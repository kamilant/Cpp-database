#include "dependencies.h"
#include "DMethods.h"
//Constructors and virtual destructor
DMethods::DMethods(std::string _name, std::string _physicalP, std::string _depictedFeature, std::string _imageType) {
    methodName = _name;
    physicalP = _physicalP;
    depictedFeature = _depictedFeature;
    imageType = _imageType;
  };
DMethods::~DMethods(){};
DMethods::DMethods(const DMethods &method){
    methodName = method.methodName;
    physicalP = method.physicalP;
    depictedFeature = method.depictedFeature;
    imageType = method.imageType;
};
//<GETTERS>
std::string DMethods::getMethodName() {
  return "- Method Name: [ "+ methodName +" ]";
};
std::string DMethods::getPhysicalPhenomena() {
  return	"- Physical Phenomena: [ " + physicalP +" ]";
};
std::string DMethods::getDepictedFeature() {
  return "- Depicted Feature: [ " + depictedFeature + " ]";
};
std::string DMethods::getImageType() {
  return "- Image Type: [ " + imageType+" ]";
};
vector<string> DMethods::getProperties(){
vector<std::string> properties;
properties.push_back("- Method Name: [ "+ methodName +" ]");
properties.push_back("- Physical Phenomena: [ " + physicalP +" ]");
properties.push_back("- Depicted Feature: [ " + depictedFeature + " ]");
properties.push_back("- Image Type: [ " + imageType+" ]");
return properties;
};
//</GETTERS>
//<SETTERS>
void DMethods::setMethodName(std::string _methodName) {
  methodName = _methodName;
};
void DMethods::setPhysicalPhenomena(std::string _physicalPhenomena) {
  physicalP = _physicalPhenomena;
};
void DMethods::setDepictedFeature(std::string _depictedFeature) {
  depictedFeature = _depictedFeature;
};
void DMethods::setImageType(std::string _imageType) {
  imageType = _imageType;
};
//</SETTERS>
//METHODS
