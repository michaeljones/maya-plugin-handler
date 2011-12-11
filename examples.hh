#ifndef EXAMPLES_HH
#define EXAMPLES_HH

#include <maya/MPxLocatorNode.h>
#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>

class Locator : public MPxLocatorNode
{
public:

    static MTypeId id;
    static void* creator() { return new Locator; }
    static MStatus initialize() { return MS::kSuccess; }

    static MString nodeName;
    static MPxNode::Type nodeType;
    static MString* classification;

};

class Command : public MPxCommand
{
public:

    static void* creator() { return new Locator; }
    static MSyntax syntaxCreator() { return MSyntax(); }

    static MString commandName;

};


#endif // EXAMPLES_HH


