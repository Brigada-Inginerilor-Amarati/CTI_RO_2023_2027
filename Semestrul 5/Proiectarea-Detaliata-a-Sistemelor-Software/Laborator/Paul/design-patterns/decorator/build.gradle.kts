plugins {
    kotlin("jvm") version "2.2.20"
    application
}

application {
    mainClass.set("org.paul.MainKt")
}

group = "org.paul"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(kotlin("test"))
}

tasks.test {
    useJUnitPlatform()
}
kotlin {
    jvmToolchain(22)
}