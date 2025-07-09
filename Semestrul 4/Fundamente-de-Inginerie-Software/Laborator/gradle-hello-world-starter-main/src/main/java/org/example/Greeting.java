package org.example;

import org.fusesource.jansi.Ansi;

import java.util.Properties;

public class Greeting {

    private final Properties properties;

    public Greeting(String language) {
        properties = PropertiesUtils.getPropertiesForLanguage(language);
    }

    public String getGreeting() {
        return properties.getProperty("greeting.text");
    }

    public Ansi.Color getGreetingColor() {
        return getAnsiColor("greeting.color");
    }

    public String getPerson() {
        return properties.getProperty("person.text");
    }

    public Ansi.Color getPersonColor() {
        return getAnsiColor("person.color");
    }

    public String getPunctuation() {
        return properties.getProperty("punctuation.text");
    }

    public Ansi.Color getPunctuationColor() {
        return getAnsiColor("punctuation.color");
    }

    private Ansi.Color getAnsiColor(String PERSON_COLOR_PROPERTY) {
        try {
            return Ansi.Color.valueOf(properties.getProperty(PERSON_COLOR_PROPERTY).toUpperCase());
        } catch (IllegalArgumentException e) {
            return Ansi.Color.DEFAULT;
        }
    }
}