<?php

// autoload_static.php @generated by Composer

namespace Composer\Autoload;

class ComposerStaticInitb04cf18eaf5ea3ee75d330c1d6973c4e
{
    public static $classMap = array (
        'Composer\\InstalledVersions' => __DIR__ . '/..' . '/composer/InstalledVersions.php',
    );

    public static function getInitializer(ClassLoader $loader)
    {
        return \Closure::bind(function () use ($loader) {
            $loader->classMap = ComposerStaticInitb04cf18eaf5ea3ee75d330c1d6973c4e::$classMap;

        }, null, ClassLoader::class);
    }
}
