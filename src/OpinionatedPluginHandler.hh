#ifndef OPINIONATEDPLUGINHANDLER_HH
#define OPINIONATEDPLUGINHANDLER_HH

#include <maya/MFnPlugin.h>

namespace mph
{

//
// Compile time detection of T::nodeType member
//
template< class T >
class NodeTypeIsPresent
{
    // Objects to use as different sized return values
    class Yes { char a[10]; };
    class No { char a[1]; };

    // Dummy struct which allows us to enforce the type of the nodeType member, though we have to
    // make it a pointer type as the location of the member if non-const but the value isn't and
    // only non-const expressions can be used for templates
    template< class U, MPxNode::Type* > struct Check {};

    // Functions to match with different sized return values
    template< class U > static Yes func( Check< U, &U::nodeType >* );
    template< class U > static No func( ... );

public:

    // Define enum with value of 1 if we can successfully match the overloaded version of func which
    // requires a type that has a member called nodeType which is of type MPxNode::Type
    enum { value = sizeof( func< T >( NULL ) ) == sizeof( Yes ) ? 1 : 0 };
};


// To be used with NodeTypeIsPresent< T >::value as the second template argument like:
//
//     NodeType< T, NodeTypeIsPresent< T >::value >
//
// Default case for types which don't have appropriate nodeType member. The compiler will use this
// if it can't match the more specific one below. The nodeTyp method returns the expected default
// argument for the nodeType argument for MFnPlugin::registerNode
template< class T, int >
class NodeType
{
public:

    static const MPxNode::Type nodeType() { return MPxNode::kDependNode; }
};

// Matched when T has the appropriate nodeType member, the static nodeType member here returns the
// value of the nodeType member from T.
template< class T >
class NodeType< T, 1 >
{
public:

    static const MPxNode::Type nodeType() { return T::nodeType; };
};

//
// Compile time detection of T::classification member
//
// Works as the nodeType detection above so we leave out the comments
//
template< class T >
class ClassificationIsPresent
{
    class Yes { char a[10]; };
    class No { char a[1]; };

    template< class U, MString* > struct Check {};
    template< class U > static Yes func( Check< U, &U::classification >* );
    template< class U > static No func( ... );

public:

    enum { value = sizeof( func< T >( 0 ) ) == sizeof( Yes ) ? 1 : 0 };
};


template< class T, int >
class Classification
{
public:

    static const MString* classification() { return NULL; }
};

template< class T >
class Classification< T, 1 >
{
public:

    static const MString* classification() { return &T::classification; };
};


//
// Compile time detection of T::dataType member
//
// Works as the nodeType detection above so we leave out the comments
//
template< class T >
class DataTypeIsPresent
{
    class Yes { char a[10]; };
    class No { char a[1]; };

    template< class U, MPxData::Type* > struct Check {};
    template< class U > static Yes func( Check< U, &U::dataType >* );
    template< class U > static No func( ... );

public:

    enum { value = sizeof( func< T >( 0 ) ) == sizeof( Yes ) ? 1 : 0 };
};


template< class T, int >
class DataType
{
public:

    static const MPxData::Type dataType() { return MPxData::kData; }
};

template< class T >
class DataType< T, 1 >
{
public:

    static const MPxData::Type dataType() { return T::dataType; };
};


//
// Compile time detection of T::syntaxCreator member
//
// Works as the nodeType detection above so we leave out the comments
//
template< class T >
class SyntaxCreatorIsPresent
{
    class Yes { char a[10]; };
    class No { char a[1]; };

    template< class U, MCreateSyntaxFunction > struct Check {};
    template< class U > static Yes func( Check< U, &U::syntaxCreator >* );
    template< class U > static No func( ... );

public:

    enum { value = sizeof( func< T >( 0 ) ) == sizeof( Yes ) ? 1 : 0 };
};


template< class T, int >
class SyntaxCreator
{
public:

    static const MCreateSyntaxFunction syntaxCreator() { return NULL; }
};

template< class T >
class SyntaxCreator< T, 1 >
{
public:

    static const MCreateSyntaxFunction syntaxCreator() { return T::syntaxCreator; };
};

//
//  InitializeOpinionatedPluginHandler
//
class InitializeOpinionatedPluginHandler
{
public:

    InitializeOpinionatedPluginHandler( MFnPlugin& pluginFn )
     : m_pluginFn( pluginFn ) {}

    template< class NodeT >
    MStatus handleNode()
    {
        return m_pluginFn.registerNode(
                NodeT::nodeName,
                NodeT::id,
                NodeT::creator,
                NodeT::initialize,
                NodeType< NodeT, NodeTypeIsPresent< NodeT >::value >::nodeType(),
                Classification< NodeT, ClassificationIsPresent< NodeT >::value >::classification()
                );
    }

    template< class CommandT >
    MStatus handleCommand()
    {
        return m_pluginFn.registerCommand(
                CommandT::commandName,
                CommandT::creator,
                SyntaxCreator<
                    CommandT,
                    SyntaxCreatorIsPresent< CommandT >::value
                    >::syntaxCreator()
                );
    }

    template< class DataT >
    MStatus handleData()
    {
        return m_pluginFn.registerData(
                DataT::dataName,
                DataT::id,
                DataT::creator,
                DataType< DataT, DataTypeIsPresent< DataT >::value >::dataType()
                );
    }

    template< class ControlCommandT >
    MStatus handleControlCommand()
    {
        return m_pluginFn.registerControlCommand(
                ControlCommandT::commandName,
                ControlCommandT::creator
                );
    }

private:

    MFnPlugin& m_pluginFn;
};


//
//  UninitializeOpinionatedPluginHandler
//
class UninitializeOpinionatedPluginHandler
{
public:

    UninitializeOpinionatedPluginHandler( MFnPlugin& pluginFn )
     : m_pluginFn( pluginFn ) {}

    template< class NodeT >
    MStatus handleNode()
    {
        return m_pluginFn.deregisterNode( NodeT::id );
    }

    template< class CommandT >
    MStatus handleCommand()
    {
        return m_pluginFn.deregisterCommand( CommandT::commandName );
    }

    template< class DataT >
    MStatus handleData()
    {
        return m_pluginFn.deregisterData( DataT::id );
    }

    template< class ControlCommandT >
    MStatus handleControlCommand()
    {
        return m_pluginFn.deregisterControlCommand( ControlCommandT::commandName );
    }

private:

    MFnPlugin& m_pluginFn;
};

}; // end namespace mph

#endif // OPINIONATEDPLUGINHANDLER_HH


