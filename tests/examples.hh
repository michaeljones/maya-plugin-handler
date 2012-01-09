#ifndef EXAMPLES_HH
#define EXAMPLES_HH

#include <maya/MPxLocatorNode.h>
#include <maya/MPxCommand.h>
#include <maya/MPxData.h>
#include <maya/MSyntax.h>

//
//  Standard classes - used for the Polymorphic approach
//
class Locator : public MPxLocatorNode
{
public:

    static MTypeId id;
    static void* creator() { return new Locator; }
    static MStatus initialize() { return MS::kSuccess; }
};

class Command : public MPxCommand
{
public:

    static void* creator() { return new Command; }
    static MSyntax syntaxCreator() { return MSyntax(); }
};

class Data : public MPxData
{
public:

    static MTypeId id;
    static void* creator() { return new Command; }
    static MSyntax syntaxCreator() { return MSyntax(); }
};


//
//  Opinionated Classes - used for the Template approach, provide examples of classes with some &
//  all of the possible static members
//
class FullOpinionatedLocator : public MPxLocatorNode
{
public:

    static MTypeId id;
    static void* creator() { return new FullOpinionatedLocator; }
    static MStatus initialize() { return MS::kSuccess; }

    static MString nodeName;
    static MPxNode::Type nodeType;
    static MString classification;

};

class PartialOpinionatedNode : public MPxNode
{
public:

    static MTypeId id;
    static void* creator() { return new PartialOpinionatedNode; }
    static MStatus initialize() { return MS::kSuccess; }

    static MString nodeName;
};

class FullOpinionatedCommand : public MPxCommand
{
public:

    static void* creator() { return new FullOpinionatedCommand; }
    static MSyntax syntaxCreator() { return MSyntax(); }

    static MString commandName;
};

class PartialOpinionatedCommand : public MPxCommand
{
public:

    static void* creator() { return new PartialOpinionatedCommand; }

    static MString commandName;
};

class FullOpinionatedData : public MPxData
{
public:

    void copy( const MPxData& ) {};
    MTypeId typeId() const { return id; };
    MString name() const { return dataName; };

    static MTypeId id;
    static void* creator() { return new FullOpinionatedData; }
    static MStatus initialize() { return MS::kSuccess; }

    static MString dataName;
    static MPxData::Type dataType;
};

class PartialOpinionatedData : public MPxData
{
public:

    void copy( const MPxData& ) {};
    MTypeId typeId() const { return id; };
    MString name() const { return dataName; };

    static MTypeId id;
    static void* creator() { return new Command; }
    static MSyntax syntaxCreator() { return MSyntax(); }

    static MString dataName;
};


#endif // EXAMPLES_HH


