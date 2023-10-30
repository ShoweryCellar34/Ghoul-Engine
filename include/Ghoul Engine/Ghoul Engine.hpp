#pragma once
#include "../GLAD/glad.h"
#include "../IMGUI/imgui.h"
#include "../IMGUI/imgui_stdlib.h"
#include "../IMGUI/imgui_impl_sdl2.h"
#include "../IMGUI/imgui_impl_opengl3.h"
#include "../SDL2/SDL.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../stb/stb_image.h"

class Logger
{
private:
    std::ofstream logFile;
    std::string tempBuffer;
    void log(std::string prefix, std::string message)
    {
        if (!save)
        {
            tempBuffer.append("[NOT SAVED]");
        }
        tempBuffer.append(prefix);
        tempBuffer.append(message);
        tempBuffer.append("\n");
        if (save)
        {
            logFile.open(logFilePath, std::ios::app);
            logFile << tempBuffer;
            logFile.close();
        }
        if (print)
        {
            std::cout << tempBuffer;
        }
        tempBuffer.clear();
    }

public:
    std::string logFilePath = "log.txt";
    bool print = true;
    bool save = true;
    void Note(std::string message)
    {
        log("[NOTE] ", message);
    }
    void Warn(std::string message)
    {
        log("[WARN] ", message);
    }
    void Error(std::string message)
    {
        log("[ERROR] ", message);
    }
    void FatalError(std::string message)
    {
        log("[FATAL ERROR] ", message);
    }
    Logger()
    {
        logFile.open(logFilePath);
        logFile.clear();
        logFile.close();
    }
    Logger(bool print, bool save)
    {
        logFile.open(logFilePath);
        logFile.clear();
        logFile.close();
        this->print = print;
        this->save = save;
    }
    Logger(bool print, bool save, std::string logFilePath)
    {
        logFile.open(logFilePath);
        logFile.clear();
        logFile.close();
        this->print = print;
        this->save = save;
        this->logFilePath = logFilePath;
    }
};

class Shader
{
public:
    unsigned int shaderProgram, texture;
    Logger *log;
    Shader(std::string &vertexShaderPath, std::string &fragmentShaderPath, std::string &texturePath, Logger &log)
    {
        this->log = &log;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int imageWidth, imageHeight, imageChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *imageData = stbi_load(texturePath.c_str(), &imageWidth, &imageHeight, &imageChannels, 4);
        log.Note("Loading Texture");
        if (imageData)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            glGenerateMipmap(GL_TEXTURE_2D);
            log.Note("Loaded Texture");
        }
        else
        {
            log.Note("Failed To Load Texture");
        }
        log.Note("Freeing Image Data...");
        stbi_image_free(imageData);
        log.Note("Freed Image Data");
        glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, "texture"), 0);
        std::string vertexShaderString;
        std::string fragmentShaderString;
        std::ifstream vertexShaderSource;
        std::ifstream fragmentShaderSource;
        vertexShaderSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            log.Note("Opening Shader Files...");
            vertexShaderSource.open(vertexShaderPath);
            fragmentShaderSource.open(fragmentShaderPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vertexShaderSource.rdbuf();
            fShaderStream << fragmentShaderSource.rdbuf();
            vertexShaderSource.close();
            fragmentShaderSource.close();
            log.Note("Closed Shader Files");
            vertexShaderString = vShaderStream.str();
            fragmentShaderString = fShaderStream.str();
        }
        catch (std::ifstream::failure error)
        {
            log.Error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        }
        const char *vertexShaderCode = vertexShaderString.c_str();
        const char *fragmentShaderCode = fragmentShaderString.c_str();
        unsigned int vertexShader, fragmentShader;
        log.Note("Creating Shaders...");
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
        glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            log.Error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
            log.Error(infoLog);
        }
        else
        {
            log.Note("Created Vertex Shader");
        }
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            log.Error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
            log.Error(infoLog);
        }
        else
        {
            log.Note("Created Fragment Shader");
        }
        log.Note("Creating Shader Program...");
        shaderProgram = glCreateProgram();
        if (shaderProgram == 0)
        {
            log.Error("Failed To Created Shader Program");
        }
        else
        {
            log.Note("Created Shader Program");
        }
        log.Note("Attaching Vertex Shader...");
        glAttachShader(shaderProgram, vertexShader);
        unsigned int failedShaderNumber = 0;
        int shaderNumber = 0;
        glGetProgramiv(shaderProgram, GL_ATTACHED_SHADERS, &shaderNumber);
        if (shaderNumber < 1)
        {
            log.Error("Failed To Attach Vertex Shader");
            failedShaderNumber++;
        }
        else
        {
            log.Note("Attached Vertex Shader");
        }
        log.Note("Attaching Fragment Shader...");
        glAttachShader(shaderProgram, fragmentShader);
        glGetProgramiv(shaderProgram, GL_ATTACHED_SHADERS, &shaderNumber);
        if (shaderNumber < 2 - failedShaderNumber)
        {
            log.Error("Failed To Attach Fragment Shader");
            failedShaderNumber++;
        }
        else
        {
            log.Note("Attached Fragment Shader");
        }
        glLinkProgram(shaderProgram);
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            log.Error("ERROR::SHADER::PROGRAM::LINKING_FAILED");
            log.Error(infoLog);
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    void use()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUseProgram(shaderProgram);
    }
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }
    void changeTexture(std::string &newTexturePath) const
    {
        int newImageWidth, newImageHeight, newImageChannels;
        unsigned char *newImageData = stbi_load(newTexturePath.c_str(), &newImageWidth, &newImageHeight, &newImageChannels, 4);
        log->Note("Loading New Texture");
        if (newImageData)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newImageWidth, newImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, newImageData);
            glGenerateMipmap(GL_TEXTURE_2D);
            log->Note("Loaded New Texture");
        }
        else
        {
            log->Note("Failed To Load New Texture");
        }
        log->Note("Freeing New Image Data...");
        stbi_image_free(newImageData);
        log->Note("Freed New Image Data");
    }
};
