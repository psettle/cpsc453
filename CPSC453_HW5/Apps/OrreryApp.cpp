/**
file: OrreryApp.cpp
brief: An app that shows the solar system
notes:
*/

/**********************************************************
                        INCLUDES
**********************************************************/

#include "OrreryApp.hpp"
#include "Sphere.hpp"
#include "SphericalCamera.hpp"

/**********************************************************
                        CONSTANTS
**********************************************************/

#define DEFAULT_SPEED      ( 1.0f )

#define SUN_RADIUS_KM      ( 695700.0f )
#define EARTH_RADIUS_KM    ( 6371.0f )
#define MOON_RADIUS_KM     ( 1727.0f )
#define MARS_RADIUS_KM     ( 3390.0f )

#define RADIUS_LOG_FACTOR     ( 1000.0f )
#define RADIUS_SCALE_FACTOR     ( 2.0f )
#define SUN_RADIUS_GL           ( RADIUS_SCALE_FACTOR * glm::log(SUN_RADIUS_KM / RADIUS_LOG_FACTOR) / glm::log(10.0f) )
#define EARTH_RADIUS_GL         ( RADIUS_SCALE_FACTOR * glm::log(EARTH_RADIUS_KM / RADIUS_LOG_FACTOR) / glm::log(10.0f) )
#define MOON_RADIUS_GL          ( RADIUS_SCALE_FACTOR * glm::log(MOON_RADIUS_KM / RADIUS_LOG_FACTOR) / glm::log(10.0f) )
#define MARS_RADIUS_GL          ( RADIUS_SCALE_FACTOR * glm::log(MARS_RADIUS_KM / RADIUS_LOG_FACTOR) / glm::log(10.0f) )

#define EARTH_ORBITAL_DISTANCE_KM   ( 149600000.0f )
#define MOON_ORBITAL_DISTANCE_KM    ( 363396.0f )
#define MARS_ORBITAL_DISTANCE_KM    ( 228000000.0f )

#define DISTANCE_SCALE_FACTOR       ( 30000.0f )
#define DISTANCE_SCALE_POWER        ( 0.4f )
#define EARTH_ORBITAL_DISTANCE_GL   ( glm::pow(EARTH_ORBITAL_DISTANCE_KM / DISTANCE_SCALE_FACTOR, DISTANCE_SCALE_POWER) )
#define MOON_ORBITAL_DISTANCE_GL    ( glm::pow(MOON_ORBITAL_DISTANCE_KM / DISTANCE_SCALE_FACTOR,  DISTANCE_SCALE_POWER) )
#define MARS_ORBITAL_DISTANCE_GL    ( glm::pow(MARS_ORBITAL_DISTANCE_KM /DISTANCE_SCALE_FACTOR,  DISTANCE_SCALE_POWER) )

/* sidereal rotational periods, this way we don't have to deal with relative rotation periods to be accurate */
/* 1s is 24 hours in my program, not 1 day as stated in the assignment, as "1 day" becomes kind of ambigous in this context. */
#define SUN_ROTATIONAL_PERIOD_S     ( 24.47f )
#define EARTH_ROTATIONAL_PERIOD_S   ( 0.9972f )
#define MOON_ROTATIONAL_PERIOD_S    ( 27.32f )
#define MARS_ROTATIONAL_PERIOD_S    ( 1.026f )

#define EARTH_ORBITAL_PERIOD_S      ( 365.25f )
#define MOON_ORBITAL_PERIOD_S       ( MOON_ROTATIONAL_PERIOD_S )
#define MARS_ORBITAL_PERIOD_S       ( 1.9f * EARTH_ORBITAL_PERIOD_S )

#define EARTH_ORBITAL_INCLINATION   ( 7.155f * PI / 180.0f )
#define MOON_ORBITAL_INCLINATION    ( 5.145f * PI / 180.0f )
#define MARS_ORBITAL_INCLINATION    ( 5.65f * PI / 180.0f )

#define EARTH_ORBITAL_TILT          ( 23.5f * PI / 180.0f )
#define MOON_ORBITAL_TILT           ( 6.68f * PI / 180.0f )
#define MARS_ORBITAL_TILT           ( 25.19f * PI / 180.0f )

/**********************************************************
                       DECLARATIONS
**********************************************************/

/**********************************************************
                       DEFINITIONS
**********************************************************/

enum TEXTURE_FILES {
    TEXTURE_EARTH_DAY,
    TEXTURE_SUN,
    TEXTURE_MOON,
    TEXTURE_MARS,
    TEXTURE_STARS,
};

static const std::vector<std::string> imagePaths = {
    "Images/8k_earth_daymap.jpg",
    "Images/8k_sun.jpg",
    "Images/8k_moon.jpg",
    "Images/8k_mars.jpg",
    "Images/8k_stars_milky_way.jpg",
};

OrreryApp::OrreryApp(IFrameDispatcher* frameDispatcher, IInputDispatcher* inputDispatcher)
    : pFrameDispatcherM(frameDispatcher), pInputDispatcherM(inputDispatcher)
{
    pInputDispatcherM->RegisterInputListener(this);
    pFrameDispatcherM->RegisterFrameListener(this);

    ConstructScene();
}

OrreryApp::~OrreryApp()
{
    for (auto shape : activeShapesM)
    {
        if (nullptr != shape)
        {
            delete shape;
        }
    }

    if (nullptr != pCameraM)
    {
        delete pCameraM;
    }

    pInputDispatcherM->UnregisterInputListener(this);
    pFrameDispatcherM->UnregisterFrameListener(this);
}

void OrreryApp::OnFrame()
{
    GLdouble time = glfwGetTime();
    GLfloat dt;

    if (prevTime > 0.0f)
    {
        dt = static_cast<GLfloat>(time - prevTime);
    }
    else
    {
        dt = 0.0f;
    }

    prevTime = time;

    if (isPausedM)
    {
        return;
    }

    dt *= speedM;
    SimulateTime(dt);
}

void OrreryApp::SimulateTime(GLfloat dt)
{
    elapsedTime += dt;

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    GLfloat sunRotationalAngle = 2 * PI * dt / SUN_ROTATIONAL_PERIOD_S;
    sceneGraphM.sunSpin = glm::rotate(sunRotationalAngle, up) * sceneGraphM.sunSpin;
    GLfloat earthRotationalAngle = 2 * PI * dt / EARTH_ROTATIONAL_PERIOD_S;
    sceneGraphM.earthSpin = glm::rotate(earthRotationalAngle, up) * sceneGraphM.earthSpin;
    GLfloat moonRotationalAngle = 2 * PI * dt / MOON_ROTATIONAL_PERIOD_S;
    sceneGraphM.moonSpin = glm::rotate(moonRotationalAngle, up) * sceneGraphM.moonSpin;
    GLfloat marsRotationalAngle = 2 * PI * dt / MARS_ROTATIONAL_PERIOD_S;
    sceneGraphM.marsSpin = glm::rotate(marsRotationalAngle, up) * sceneGraphM.marsSpin;

    glm::vec3 newPos;

    //0 out current pos:
    sceneGraphM.earthToSun[3][0] = 0.0f;
    sceneGraphM.earthToSun[3][1] = 0.0f;
    sceneGraphM.earthToSun[3][2] = 0.0f;
    //apply new pos
    newPos = CalculateOrbitalPosition(elapsedTime, EARTH_ORBITAL_DISTANCE_GL, EARTH_ORBITAL_INCLINATION, EARTH_ORBITAL_PERIOD_S);
    sceneGraphM.earthToSun = glm::translate(newPos) * sceneGraphM.earthToSun;

    //0 out current pos:
    sceneGraphM.moonToEarth[3][0] = 0.0f;
    sceneGraphM.moonToEarth[3][1] = 0.0f;
    sceneGraphM.moonToEarth[3][2] = 0.0f;
    
    //apply new pos
    newPos = CalculateOrbitalPosition(elapsedTime, MOON_ORBITAL_DISTANCE_GL, MOON_ORBITAL_INCLINATION, MOON_ORBITAL_PERIOD_S);
    sceneGraphM.moonToEarth = glm::translate(newPos) * sceneGraphM.moonToEarth;

    //0 out current pos:
    sceneGraphM.marsToSun[3][0] = 0.0f;
    sceneGraphM.marsToSun[3][1] = 0.0f;
    sceneGraphM.marsToSun[3][2] = 0.0f;
    //apply new pos
    newPos = CalculateOrbitalPosition(elapsedTime, MARS_ORBITAL_DISTANCE_GL, MARS_ORBITAL_INCLINATION, MARS_ORBITAL_PERIOD_S);
    sceneGraphM.marsToSun = glm::translate(newPos) * sceneGraphM.marsToSun;
}

glm::vec3 OrreryApp::CalculateOrbitalPosition(GLfloat elapsedTime, GLfloat radius, GLfloat inclination, GLfloat period) const
{
    glm::vec3 pos;
    pos.x = radius * glm::sin(2 * PI * elapsedTime / period);
    pos.z = radius * glm::cos(2 * PI * elapsedTime / period);
    pos.y = radius * glm::tan(inclination) * glm::sin(2 * PI * elapsedTime / period);
    return pos;
}

void OrreryApp::OnKey(GLint key, GLint action)
{
    if (action != GLFW_RELEASE)
    {
        return;
    }

    switch (key)
    {
    case GLFW_KEY_SPACE:
        isPausedM = !isPausedM;
        break;
    case GLFW_KEY_RIGHT:
        speedM *= 1.5f;
        break;
    case GLFW_KEY_LEFT:
        speedM /= 1.5f;
        break;
    case GLFW_KEY_R:
        SimulateTime(-elapsedTime);
        break;
    }
}

void OrreryApp::OnScroll(GLdouble scroll)
{

}

void OrreryApp::OnMouseMove(GLdouble xpos, GLdouble ypos)
{

}

void OrreryApp::OnMouseButton(GLint button, GLint action)
{

}

void OrreryApp::ConstructScene()
{
    pCameraM = new SphericalCamera(pFrameDispatcherM, pInputDispatcherM);

    pSunM = new Sphere(pFrameDispatcherM, pCameraM, SUN_RADIUS_GL, imagePaths[TEXTURE_SUN], 1.0f, 0.0f);
    pEarthM = new Sphere(pFrameDispatcherM, pCameraM, EARTH_RADIUS_GL, imagePaths[TEXTURE_EARTH_DAY], 0.5f, 1.0f);
    pMoonM = new Sphere(pFrameDispatcherM, pCameraM, MOON_RADIUS_GL, imagePaths[TEXTURE_MOON], 0.5f, 1.0f);
    pMarsM = new Sphere(pFrameDispatcherM, pCameraM, MARS_RADIUS_GL, imagePaths[TEXTURE_MARS], 0.5f, 1.0f);
    pStarsM = new Sphere(pFrameDispatcherM, pCameraM, MARS_ORBITAL_DISTANCE_GL * 1000.0f, imagePaths[TEXTURE_STARS], 1.0f, 0.0f);

    pSunM->AddSceneReference(&sceneGraphM.sunToWorld);
    pSunM->AddSceneReference(&sceneGraphM.sunRotation);
    pSunM->AddSceneReference(&sceneGraphM.sunSpin);

    pEarthM->AddSceneReference(&sceneGraphM.sunToWorld);
    pEarthM->AddSceneReference(&sceneGraphM.earthToSun);
    pEarthM->AddSceneReference(&sceneGraphM.earthRotation);
    pEarthM->AddSceneReference(&sceneGraphM.earthSpin);

    pMarsM->AddSceneReference(&sceneGraphM.sunToWorld);
    pMarsM->AddSceneReference(&sceneGraphM.marsToSun);
    pMarsM->AddSceneReference(&sceneGraphM.marsRotation);
    pMarsM->AddSceneReference(&sceneGraphM.marsSpin);

    pMoonM->AddSceneReference(&sceneGraphM.sunToWorld);
    pMoonM->AddSceneReference(&sceneGraphM.earthToSun);
    pMoonM->AddSceneReference(&sceneGraphM.moonToEarth);
    pMoonM->AddSceneReference(&sceneGraphM.moonRotation);
    pMoonM->AddSceneReference(&sceneGraphM.moonSpin);

    sceneGraphM.earthRotation = glm::rotate(EARTH_ORBITAL_TILT, glm::vec3(0.0f, 0.0f, 1.0f)) * sceneGraphM.earthRotation;
    sceneGraphM.moonRotation = glm::rotate(MOON_ORBITAL_TILT, glm::vec3(0.0f, 0.0f, 1.0f)) * sceneGraphM.moonRotation;
    sceneGraphM.marsRotation = glm::rotate(MARS_ORBITAL_TILT, glm::vec3(0.0f, 0.0f, 1.0f)) * sceneGraphM.marsRotation;

    /* Apply rotation to the moon such that the correct face is towards the earth. */
    sceneGraphM.moonRotation = glm::rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * sceneGraphM.moonRotation;

    activeShapesM.push_back(pSunM);
    activeShapesM.push_back(pEarthM);
    activeShapesM.push_back(pMoonM);
    activeShapesM.push_back(pMarsM);
}