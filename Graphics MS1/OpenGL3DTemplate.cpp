#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glut.h>

GLuint textureID; // Texture ID
float rotAng;
float camera_rot;

void loadTexture() {
    int width, height, channels;
    unsigned char* image = stbi_load("C:/Users/farid/OneDrive/Desktop/Graphics MS1/dear.jpeg", &width, &height, &channels, 0);
    if (image == NULL) {
        printf("Failed to load texture\n");
        return;
    }
    printf("Image loaded successfully: Width=%d, Height=%d, Channels=%d\n", width, height, channels);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Assign the image to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Free image data
    stbi_image_free(image);
}

void Display(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);  // Enable automatic normalization of normals
    glEnable(GL_TEXTURE_2D);  // Enable texture mapping
    glBindTexture(GL_TEXTURE_2D, textureID);



    GLfloat light_direction[] = { -1.0f, 1.0f, -1.0f, 1.0f };  // Light from upper-right corner
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Set material properties for the Lego head (Yellow)
    GLfloat head_diffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };  // Yellow diffuse color
    GLfloat head_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };  // Adjust specular properties
    GLfloat head_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };  // Adjust ambient properties

    glMaterialfv(GL_FRONT, GL_DIFFUSE, head_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, head_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, head_ambient);


    // Lego head
    glPushMatrix();
    glRotatef(rotAng, 0, 1, 0);
    glutSolidSphere(0.4, 25, 25);
    glPopMatrix();



    // Set material properties for the Lego body
    GLfloat body_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat body_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat body_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, body_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, body_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, body_ambient);

    // Lego body
    glPushMatrix();
    glRotatef(-rotAng, 0, 1, 0);
    glTranslatef(0, -0.8, 0);
    glColor3f(1.0f, 0.0f, 0.0f); // Apply white color to blend with the texture

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 0.5);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 0.5);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 0.5);


    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
    glPopMatrix();


    // Set material properties for the first leg
    GLfloat leg_diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat leg_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat leg_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, leg_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, leg_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, leg_ambient);

    // First leg
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue
    glTranslatef(0.2, -1.6, 0);
    glScalef(0.3, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Set material properties for the second leg
    GLfloat leg2_diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat leg2_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat leg2_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, leg2_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, leg2_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, leg2_ambient);

    // Second leg
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue
    glTranslatef(-0.3, -1.6, 0);
    glScalef(0.3, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Set material properties for the first arm
    GLfloat arm_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat arm_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat arm_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, arm_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, arm_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, arm_ambient);

    // First arm
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);  // Red
    glTranslatef(0.6, -0.6, 0);
    glScalef(0.2, 0.7, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    // Set material properties for the second arm
    GLfloat arm2_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat arm2_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat arm2_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, arm2_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, arm2_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, arm2_ambient);

    // Second arm
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);  // Red
    glTranslatef(-0.6, -0.6, 0);
    glScalef(0.2, 0.7, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    // Set material properties for the hands
    GLfloat hand_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat hand_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat hand_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, hand_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, hand_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, hand_ambient);

    // Right hand
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);  // Red
    glTranslatef(0.65, -1.15, 0);
    glutSolidSphere(0.18, 30, 30);
    glPopMatrix();

    // Left hand
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);  // Red
    glTranslatef(-0.65, -1.15, 0);
    glutSolidSphere(0.18, 30, 30);
    glPopMatrix();

    //glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
    glFlush();
}

void Anim() {
    rotAng += 0.0;
    glutPostRedisplay();
}

void main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(300, 300);
    glutInitWindowPosition(150, 150);

    glutCreateWindow("Samir");
    glutDisplayFunc(Display);
    glutIdleFunc(Anim);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    // Load and bind texture
    loadTexture();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 300 / 300, 0.1f, 300.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0f, 1.0f, 5.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glutMainLoop();
}
