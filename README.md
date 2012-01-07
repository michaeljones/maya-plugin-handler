
maya-plugin-handler
===================

C++ helper classes to reduce code duplication between initializePlugin &
uninitializePlugin.

Status
------

The code is in early stages and hasn't be tested with complex production
plugins. It works in the basic tests but might fail in other scenarios.

Why?
----

The standard way of writing the initializePlugin and uninitializePlugin
functions for a Maya plugin generally requires very similar code in each when
it comes to registering and deregistering parts of your plugin.

It seems reasonable to try to combine these so that you only have to write one
function and it can be used for both registering and deregistering.

How?
----

There are two approaches taken here.

- `PluginHandler.hh` provides `InitializePluginHandler` and
  `UninitializePluginHandler` classes which share a `PluginHandler` base class
  and so can be treated polymorphically.
- `OpinionatedPluginHandler.hh` provides `InitializeOpinionatedPluginHandler`
  and `UninitializeOpinionatedPluginHandler` which are designed be used with a
  templated function in a minimalist way which relies on the classes that are
  being registered providing adequate information as static member variables.

Polymorphic Approach
--------------------

This allows us to write a function like:

```
MStatus handlePlugin( PluginHandler& handler )
{
    return handler.handleNode(
            "locatorExample",
            Locator::id,
            Locator::creator,
            Locator::initialize,
            MPxNode::kLocatorNode
            );
}
```

And call it from the `initializePlugin` function with an
`InitializePluginHandler` and from the `uninitializePlugin` function with an
`UninitializePluginHandler`:

```
MStatus initializePlugin( MObject obj )
{
    MFnPlugin plugin( obj, "Michael Jones", "0.1", "Any");

    InitializePluginHandler handler( plugin );
    return handlePlugin( handler );
}

MStatus uninitializePlugin( MObject obj)
{
    MFnPlugin plugin( obj );

    UninitializePluginHandler handler( plugin );
    return handlePlugin( handler );
}
```

The `InitializePluginHandler` passes all the information through to the
appropriate MFnPlugin `register` method and uses the expected default values for
optional arguments.

The `UninitializePluginHandler` ignores most of the arguments and uses the
appropriate identifier for the necessary `deregister` method on the MFnPlugin.

See `tests/example-plugin.cc` for a complete example.

Template Approach
-----------------

The template approach is a little more opinionated. It requires the arguments
to the `register` and `deregister` methods to be provided as static members of
the classes being registered and deregistered.

It allows us to write a function like this:

```
template< class OpinionatedPluginHandlerT >
MStatus handlePlugin( OpinionatedPluginHandlerT& handler )
{
    return handler.template handleNode< LocatorNode >();
}
```

And call it like:

```
MStatus initializePlugin( MObject obj )
{
    MFnPlugin plugin( obj, "Michael Jones", "0.1", "Any");

    InitializeOpinionatedPluginHandler handler( plugin );
    return handlePlugin( handler );
}

MStatus uninitializePlugin( MObject obj)
{
    MFnPlugin plugin( obj );

    UninitializeOpinionatedPluginHandler handler( plugin );
    return handlePlugin( handler );
}
```

For arguments that have defaults in the Maya API it is not necessary to provide
static members. Their presence is detected and defaults are used as a fall back
if they are not there.

The advantage here is that the registration code is minimal and it enforces a
convention for how to name and specify some details, like the creator function
and syntax functions, however some registration details are not needed anywhere
else so having them as static members of the classes seems a little
unnecessary.  


