# RayMob

AdMob support for Raylib on Android .

## How to use ?

Open the `gradle.properties` file and fill in the values for your application, such as the app name, package name, version, etc.

Make sure not to modify the occurrences of `com.bigfoot.raymob` as they will be automatically replaced during compilation with the information provided in `gradle.properties`.

The only thing you need to manually change is the advertising ID in `NativeLoader.java`. By default, it's set up for displaying interstitial ads with AdMob. If you want to add custom ads, feel free to modify this part.

Additionally, pre-compiled static libraries of Raylib for all Android-compatible architectures are already included. You'll find an extra declaration, `GetAndroidApp()`, which provides access to the `struct android_app` and can be useful for various purposes.

That's it! The process is straightforward, and everything will be handled automatically.

## Enjoy!
