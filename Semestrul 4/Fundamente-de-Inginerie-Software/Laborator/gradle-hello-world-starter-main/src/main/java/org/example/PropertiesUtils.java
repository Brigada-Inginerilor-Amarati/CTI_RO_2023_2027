package org.example;

import java.util.Properties;

public class PropertiesUtils {

    public static Properties getPropertiesForLanguage(String language) {
        Properties properties = new Properties();
        try {
            properties.load(PropertiesUtils.class.getResourceAsStream("/" + language + ".properties"));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return properties;
    }
}