# Application
<img src="src/resources/org.nickvision.application.png" width="100" height="100"/>

 **A template for creating Nickvision applications**

# Features
- Modern GTK 4 and libadwaita design
  - System/Light/Dark theme support
- Modern C++ codebase
- Support for saving application settings via a json configuration

# Chat
<a href='https://matrix.to/#/#nickvision:matrix.org'><img width='140' alt='Join our room' src='https://user-images.githubusercontent.com/17648453/196094077-c896527d-af6d-4b43-a5d8-e34a00ffd8f6.png'/></a>

# Screenshots
![MainWindow](https://user-images.githubusercontent.com/17648453/188352482-90eeeb3c-25de-4b7c-9270-c49b7692485b.png)
![FolderOpen](https://user-images.githubusercontent.com/17648453/188352502-08cfd064-c8ef-4cc3-8235-f63cbe3697c1.png)
![DarkMode](https://user-images.githubusercontent.com/17648453/188352505-75b12b3f-172b-448f-896b-1217dfe4b0a5.png)
![PreferencesDialog](https://user-images.githubusercontent.com/17648453/188352511-89444eb7-7cfb-4c8d-83f5-93d339c8ed2a.png)
![ShortcutsDialog](https://user-images.githubusercontent.com/17648453/188636456-c10370c6-0d01-47d5-8544-2ee90feefcf0.png)
![AboutDialog](https://user-images.githubusercontent.com/17648453/188543750-3e228bc8-4ecd-4c70-a733-1b6d6a28e1a8.png)

# Translating
Everyone is welcome to translate this app into their native or known languages, so that the application is accessible to everyone.

To translate the app, fork the repository and clone it locally. Make sure that `meson` is installed. Run the commands in your shell while in the directory of repository:
```bash
meson build
cd build
meson compile org.nickvision.application-pot
```
This would generate a `NickvisionApplication/po/org.nickvision.application.pot` file, now you can use this file to translate the strings into your target language. You may use [Gtranslator](https://flathub.org/apps/details/org.gnome.Gtranslator) or [poedit.com](https://poedit.com) if you do not know how to translate manually in text itself. After translating (either through tools or directly in text editor), make sure to include the required metadata on the top of translation file (see existing files in `NickvisionApplication/po/` directory.)

One particular thing you should keep in mind is that some strings in this project are bifurcated into multiple strings to cater to responsiveness of the application, like:
```
msgid ""
"If checked, the currency symbol will be displayed on the right of a monetary "
"value."
```
You should use the same format for translated strings as well. But, because all languages do not have the same sentence structure, you may not need to follow this word-by-word, rather you should bifurcate the string in about the same ratio. (For examples, look into translations of languages which do not have a English-like structure in `NickvisionApplication/po/`)

Put your translated file in `NickvisionApplication/po` directory in format `<LANG>.po` where `<LANG>` is the language code.

Put the language code of your language in `NickvisionApplication/po/LINGUAS` (this file, as a convention, should remain in alphabetical order.)

Commit these changes, and then create a pull request to the project.

As more strings may be added in the application in future, the following command needs to be ran to update all the `.po` files, which would add new strings to be translated without altering the already translated strings. But, because running this command would do this for all the languages, generally a maintainer would do that.

```bash
meson compile org.nickvision.application-update-po
```

The upper command needs to be run in `build` directory generated by `meson`.

# Dependencies
- [C++20](https://en.cppreference.com/w/cpp/20)
- [GTK 4](https://www.gtk.org/)
- [libadwaita](https://gnome.pages.gitlab.gnome.org/libadwaita/)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

