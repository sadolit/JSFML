#include <JSFML/JNI/org_jsfml_graphics_RenderWindow.h>

#include <JSFML/Intercom/Color.hpp>
#include <JSFML/Intercom/ContextSettings.hpp>
#include <JSFML/Intercom/Event.hpp>
#include <JSFML/Intercom/IntRect.hpp>
#include <JSFML/Intercom/NativeObject.hpp>
#include <JSFML/Intercom/JavaEnum.hpp>
#include <JSFML/Intercom/JavaString.hpp>
#include <JSFML/Intercom/RenderStates.hpp>
#include <JSFML/Intercom/Time.hpp>
#include <JSFML/Intercom/Vector2f.hpp>
#include <JSFML/Intercom/Vector2i.hpp>
#include <JSFML/Intercom/Vector2u.hpp>
#include <JSFML/Intercom/Vertex.hpp>
#include <JSFML/Intercom/VideoMode.hpp>

#include <JSFML/JNI/org_jsfml_ExPtr.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>

#define VERTEX_BUFSIZE_RWINDOW 0x400
sf::Vertex sfVertexBuffer_RenderWindow[VERTEX_BUFSIZE_RWINDOW];

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    nativeCreate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_jsfml_graphics_RenderWindow_nativeCreate (JNIEnv *env, jobject obj) {
    sf::RenderWindow* renderWindow = new sf::RenderWindow();

    JSFML::NativeObject::SetExPointer(env, obj, org_jsfml_ExPtr_RENDER_TARGET,
        dynamic_cast<sf::RenderTarget*>(renderWindow));

    JSFML::NativeObject::SetExPointer(env, obj, org_jsfml_ExPtr_WINDOW,
        dynamic_cast<sf::Window*>(renderWindow));

    return (jlong)renderWindow;
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    nativeDelete
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_jsfml_graphics_RenderWindow_nativeDelete (JNIEnv *env, jobject obj) {
    delete THIS(sf::RenderWindow);
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    nativeClear
 * Signature: (Lorg/jsfml/graphics/Color;)V
 */
JNIEXPORT void JNICALL Java_org_jsfml_graphics_RenderWindow_nativeClear (JNIEnv *env, jobject obj, jobject color) {
    THIS(sf::RenderWindow)->clear(JSFML::Color::ToSFML(env, color));
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    nativeSetView
 * Signature: (Lorg/jsfml/graphics/View;)V
 */
JNIEXPORT void JNICALL Java_org_jsfml_graphics_RenderWindow_nativeSetView (JNIEnv *env, jobject obj, jobject view) {
    THIS(sf::RenderWindow)->setView(*JSFML::NativeObject::GetPointer<sf::View>(env, view));
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    nativeGetDefaultView
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_jsfml_graphics_RenderWindow_nativeGetDefaultView (JNIEnv *env, jobject obj) {
    return (jlong)&THIS(sf::RenderWindow)->getDefaultView();
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    nativeGetViewport
 * Signature: (Lorg/jsfml/graphics/View;)Lorg/jsfml/graphics/IntRect;
 */
JNIEXPORT jobject JNICALL Java_org_jsfml_graphics_RenderWindow_nativeGetViewport (JNIEnv *env, jobject obj, jobject view) {
    return JSFML::IntRect::FromSFML(
        env,
        THIS(sf::RenderWindow)->getViewport(*JSFML::NativeObject::GetPointer<sf::View>(env, view)));
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    nativeConvertCoords
 * Signature: (Lorg/jsfml/system/Vector2i;Lorg/jsfml/graphics/View;)Lorg/jsfml/system/Vector2f;
 */
JNIEXPORT jobject JNICALL Java_org_jsfml_graphics_RenderWindow_nativeConvertCoords
    (JNIEnv *env, jobject obj, jobject point, jobject view) {

    if(view == NULL) {
        return JSFML::Vector2f::FromSFML(env,
            THIS(sf::RenderWindow)->convertCoords(
                JSFML::Vector2i::ToSFML(env, point)));
    } else {
        return JSFML::Vector2f::FromSFML(env,
            THIS(sf::RenderWindow)->convertCoords(
                JSFML::Vector2i::ToSFML(env, point),
                *JSFML::NativeObject::GetPointer<sf::View>(env, view)));
    }
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    nativeDraw
 * Signature: ([Lorg/jsfml/graphics/Vertex;Lorg/jsfml/graphics/PrimitiveType;Lorg/jsfml/graphics/RenderStates;)V
 */
JNIEXPORT void JNICALL Java_org_jsfml_graphics_RenderWindow_nativeDraw___3Lorg_jsfml_graphics_Vertex_2Lorg_jsfml_graphics_PrimitiveType_2Lorg_jsfml_graphics_RenderStates_2
    (JNIEnv *env, jobject obj, jobjectArray vertices, jobject type, jobject renderStates) {

    jint num = env->GetArrayLength(vertices);
    if(num > 0) {
        for(jint i = 0; i < num; i++)
            sfVertexBuffer_RenderWindow[i] = JSFML::Vertex::ToSFML(env, env->GetObjectArrayElement(vertices, i));

        THIS(sf::RenderWindow)->draw(
            sfVertexBuffer_RenderWindow,
            num,
            (sf::PrimitiveType)JavaEnum::ordinal(env, type),
            JSFML::RenderStates::ToSFML(env, renderStates));
    }
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    pushGLStates
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_jsfml_graphics_RenderWindow_pushGLStates (JNIEnv *env, jobject obj) {
    THIS(sf::RenderWindow)->pushGLStates();
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    popGLStates
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_jsfml_graphics_RenderWindow_popGLStates (JNIEnv *env, jobject obj) {
    THIS(sf::RenderWindow)->popGLStates();
}

/*
 * Class:     org_jsfml_graphics_RenderWindow
 * Method:    resetGLStates
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_jsfml_graphics_RenderWindow_resetGLStates (JNIEnv *env, jobject obj) {
    THIS(sf::RenderWindow)->resetGLStates();
}
