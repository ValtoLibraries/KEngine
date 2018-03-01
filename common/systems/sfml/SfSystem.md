# [SfSystem](SfSystem.hpp)

`System` that displays entities in an SFML window.

`SfSystem` is provided as a plugin. If the `KENGINE_SFML` option is set to `TRUE` in the project's `CMakeLists.txt`, the `SfSystem` will be automatically built into a shared library, in the `CMAKE_LIBRARY_OUTPUT_DIRECTORY`. Client code must then load the plugin (with [loadSystems](../../../SystemManager.md) for instance) at runtime.

### Using SfSystem

##### 'Normal' objects

`SfSystem` reads the resource file to be used for a `GameObject` from its [GraphicsComponent](../../components/GraphicsComponent.md)'s `appearance` property.

If `appearance` was previously registered as an abstract appearance through a [RegisterAppearance](../../packets/RegisterAppearance.hpp) datapacket, the resource file that was associated to it is loaded instead.

`SfSystem` expects `GameObjects` to have a [TransformComponent3d](../../components/TransformComponent.md) component, to specify its size and position. The position's `z` property defines the "height" at which objects will be rendered.

```
/!\ That 3d is important! TransformComponent2d, 2i, 3i, 3f... Will not be detected!
```

##### Cameras

A *"default"* camera is added upon system construction, meaning typical use does not require any action. For further configuration of the rendered areas, `CameraComponents3d` can be used.

If a `GameObject` is found to have a [CameraComponent3d](../../components/CameraComponent.hpp), a camera will be added to the scene.

 The `CameraComponent3d`'s `frustrum` property defines the area to be rendered, whereas the `GameObject`'s `TransformComponent3d`'s `boundingBox` property defines the bounds of the viewport to be displayed. The `boundingBox.topLeft.y` property defines the "height" at which the camera should be rendered (higher cameras appear in front of lower ones).

Refer to [the SFML website](https://www.sfml-dev.org/tutorials/2.0/graphics-view.php) for more information about viewports.

##### GUI

If a `GameObject` is found to have a [GUIComponent](../../components/GUIComponent.md), it will be rendered as text using the information held in that `GUIComponent`.

##### Input

User input handlers can be registered through the [Input](../../packets/Input.hpp) datapackets.

If a [kengine::LuaSystem](../../systems/LuaSystem.md) is found when the `SfSystem` is constructed, the following lua functions are registered:

* `setKeyHandler(std::function<void(Sf::Keyboard::Key)> onPress, std::function<void(sf::Keyboard::Key)> onRelease)`: sets the key handler for all keys
* `setMouseButtonHandler(std::function<void(Sf::Mouse::Button, int x, int y)> onPress, std::function<void(sf::Mouse::Button, int x, int y)> onRelease)`: sets the button handler for all keys
* `setMouseMovedHandler(std::function<void(int x, int y)> func)`: sets the mouse move handler
* `getWindowSize()`: returns the window size in pixels
* `getTileSize()`: returns the tile size in pixels
* `getGridSize()`: returns the window size in tiles

### Configuration

##### sf-config.json

`SfSystem` loads its configuration from `sf-config.json`, which is automatically copied into the `CMAKE_RUNTIME_OUTPUT_DIRECTORY`.

This file should contain a single JSON object, with `windowSize`, `tileSize` and `fullScreen` properties.

`windowSize` and `tileSize` should each be JSON objects with an `x` and `y` field, defining the window resolution and the number of pixels that should be used for a `GameObject` with 1 as its `TransformComponent3d`'s `size`.

`fullScreen` is a boolean that defines whether the window should be rendered in fullscreen or not.

##### Example

```
{
    "windowSize": {
        "x": 1280,
        "y": 720
    },
    "tileSize": {
        "x": 16,
        "y": 16
    },
    "fullScreen": false
}
```


