//========================================================================
// Heightmap example program using OpenGL 3 core profile
// Copyright (c) 2010 Olivier Delannoy
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================
//
// Conversion to vkfw (and C++): John Cvelth <cvelth.mail@gmail.com>

#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#include "vkfw/vkfw.hpp"

/* Map height updates */
#define MAX_CIRCLE_SIZE         (5.0f)
#define MAX_DISPLACEMENT        (1.0f)
#define DISPLACEMENT_SIGN_LIMIT (0.3f)
#define MAX_ITER                (200)
#define NUM_ITER_AT_A_TIME      (1)

/* Map general information */
#define MAP_SIZE                (10.0f)
#define MAP_NUM_VERTICES        (80)
#define MAP_NUM_TOTAL_VERTICES  (MAP_NUM_VERTICES * MAP_NUM_VERTICES)
#define MAP_NUM_LINES                                                                              \
  (3 * (MAP_NUM_VERTICES - 1) * (MAP_NUM_VERTICES - 1) + 2 * (MAP_NUM_VERTICES - 1))

/**********************************************************************
 * Default shader programs
 *********************************************************************/

static const char *vertex_shader_text = R"(
#version 150
uniform mat4 project;
uniform mat4 modelview;
in float x;
in float y;
in float z;

void main() {
  gl_Position = project * modelview * vec4(x, y, z, 1.0);
}
)";

static const char *fragment_shader_text = R"(
#version 150
out vec4 color;
void main() {
  color = vec4(0.2, 1.0, 0.2, 1.0);
}
)";

/**********************************************************************
 * Values for shader uniforms
 *********************************************************************/

/* Frustum configuration */
static GLfloat view_angle = 45.0f;
static GLfloat aspect_ratio = 4.0f / 3.0f;
static GLfloat z_near = 1.0f;
static GLfloat z_far = 100.f;

/* Projection matrix */
static GLfloat projection_matrix[16] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                         0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

/* Model view matrix */
static GLfloat modelview_matrix[16] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

/**********************************************************************
 * Heightmap vertex and index data
 *********************************************************************/

static GLfloat map_vertices[3][MAP_NUM_TOTAL_VERTICES];
static GLuint map_line_indices[2 * MAP_NUM_LINES];

/* Store uniform location for the shaders
 * Those values are setup as part of the process of creating
 * the shader program. They should not be used before creating
 * the program.
 */
static GLuint mesh;
static GLuint mesh_vbo[4];

/**********************************************************************
 * OpenGL helper functions
 *********************************************************************/

/* Creates a shader object of the specified type using the specified text
 */
static GLuint make_shader(GLenum type, const char *text) {
  GLuint shader;
  GLint shader_ok;
  GLsizei log_length;
  char info_log[8192];

  shader = glCreateShader(type);
  if (shader != 0) {
    glShaderSource(shader, 1, (const GLchar **) &text, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (shader_ok != GL_TRUE) {
      fprintf(stderr, "ERROR: Failed to compile %s shader\n",
              (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex");
      glGetShaderInfoLog(shader, 8192, &log_length, info_log);
      fprintf(stderr, "ERROR: \n%s\n\n", info_log);
      glDeleteShader(shader);
      shader = 0;
    }
  }
  return shader;
}

/* Creates a program object using the specified vertex and fragment text
 */
static GLuint make_shader_program(const char *vs_text, const char *fs_text) {
  GLuint program = 0u;
  GLint program_ok;
  GLuint vertex_shader = 0u;
  GLuint fragment_shader = 0u;
  GLsizei log_length;
  char info_log[8192];

  vertex_shader = make_shader(GL_VERTEX_SHADER, vs_text);
  if (vertex_shader != 0u) {
    fragment_shader = make_shader(GL_FRAGMENT_SHADER, fs_text);
    if (fragment_shader != 0u) {
      /* make the program that connect the two shader and link it */
      program = glCreateProgram();
      if (program != 0u) {
        /* attach both shader and link */
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &program_ok);

        if (program_ok != GL_TRUE) {
          fprintf(stderr, "ERROR, failed to link shader program\n");
          glGetProgramInfoLog(program, 8192, &log_length, info_log);
          fprintf(stderr, "ERROR: \n%s\n\n", info_log);
          glDeleteProgram(program);
          glDeleteShader(fragment_shader);
          glDeleteShader(vertex_shader);
          program = 0u;
        }
      }
    } else {
      fprintf(stderr, "ERROR: Unable to load fragment shader\n");
      glDeleteShader(vertex_shader);
    }
  } else {
    fprintf(stderr, "ERROR: Unable to load vertex shader\n");
  }
  return program;
}

/**********************************************************************
 * Geometry creation functions
 *********************************************************************/

/* Generate vertices and indices for the heightmap
 */
static void init_map(void) {
  int i;
  int j;
  int k;
  GLfloat step = MAP_SIZE / (MAP_NUM_VERTICES - 1);
  GLfloat x = 0.0f;
  GLfloat z = 0.0f;
  /* Create a flat grid */
  k = 0;
  for (i = 0; i < MAP_NUM_VERTICES; ++i) {
    for (j = 0; j < MAP_NUM_VERTICES; ++j) {
      map_vertices[0][k] = x;
      map_vertices[1][k] = 0.0f;
      map_vertices[2][k] = z;
      z += step;
      ++k;
    }
    x += step;
    z = 0.0f;
  }
#if DEBUG_ENABLED
  for (i = 0; i < MAP_NUM_TOTAL_VERTICES; ++i) {
    printf("Vertice %d (%f, %f, %f)\n", i, map_vertices[0][i], map_vertices[1][i],
           map_vertices[2][i]);
  }
#endif
  /* create indices */
  /* line fan based on i
   * i+1
   * |  / i + n + 1
   * | /
   * |/
   * i --- i + n
   */

  /* close the top of the square */
  k = 0;
  for (i = 0; i < MAP_NUM_VERTICES - 1; ++i) {
    map_line_indices[k++] = (i + 1) * MAP_NUM_VERTICES - 1;
    map_line_indices[k++] = (i + 2) * MAP_NUM_VERTICES - 1;
  }
  /* close the right of the square */
  for (i = 0; i < MAP_NUM_VERTICES - 1; ++i) {
    map_line_indices[k++] = (MAP_NUM_VERTICES - 1) * MAP_NUM_VERTICES + i;
    map_line_indices[k++] = (MAP_NUM_VERTICES - 1) * MAP_NUM_VERTICES + i + 1;
  }

  for (i = 0; i < (MAP_NUM_VERTICES - 1); ++i) {
    for (j = 0; j < (MAP_NUM_VERTICES - 1); ++j) {
      int ref = i * (MAP_NUM_VERTICES) + j;
      map_line_indices[k++] = ref;
      map_line_indices[k++] = ref + 1;

      map_line_indices[k++] = ref;
      map_line_indices[k++] = ref + MAP_NUM_VERTICES;

      map_line_indices[k++] = ref;
      map_line_indices[k++] = ref + MAP_NUM_VERTICES + 1;
    }
  }

#ifdef DEBUG_ENABLED
  for (k = 0; k < 2 * MAP_NUM_LINES; k += 2) {
    int beg, end;
    beg = map_line_indices[k];
    end = map_line_indices[k + 1];
    printf("Line %d: %d -> %d (%f, %f, %f) -> (%f, %f, %f)\n", k / 2, beg, end,
           map_vertices[0][beg], map_vertices[1][beg], map_vertices[2][beg], map_vertices[0][end],
           map_vertices[1][end], map_vertices[2][end]);
  }
#endif
}

static void generate_heightmap__circle(float *center_x, float *center_y, float *size,
                                       float *displacement) {
  float sign;
  /* random value for element in between [0-1.0] */
  *center_x = (MAP_SIZE * rand()) / (1.0f * RAND_MAX);
  *center_y = (MAP_SIZE * rand()) / (1.0f * RAND_MAX);
  *size = (MAX_CIRCLE_SIZE * rand()) / (1.0f * RAND_MAX);
  sign = (1.0f * rand()) / (1.0f * RAND_MAX);
  sign = (sign < DISPLACEMENT_SIGN_LIMIT) ? -1.0f : 1.0f;
  *displacement = (sign * (MAX_DISPLACEMENT * rand())) / (1.0f * RAND_MAX);
}

/* Run the specified number of iterations of the generation process for the
 * heightmap
 */
static void update_map(int num_iter) {
  assert(num_iter > 0);
  while (num_iter) {
    /* center of the circle */
    float center_x;
    float center_z;
    float circle_size;
    float disp;
    size_t ii;
    generate_heightmap__circle(&center_x, &center_z, &circle_size, &disp);
    disp = disp / 2.0f;
    for (ii = 0u; ii < MAP_NUM_TOTAL_VERTICES; ++ii) {
      GLfloat dx = center_x - map_vertices[0][ii];
      GLfloat dz = center_z - map_vertices[2][ii];
      GLfloat pd = (2.0f * (float) sqrt((dx * dx) + (dz * dz))) / circle_size;
      if (fabs(pd) <= 1.0f) {
        /* tx,tz is within the circle */
        GLfloat new_height = disp + (float) (cos(pd * 3.14f) * disp);
        map_vertices[1][ii] += new_height;
      }
    }
    --num_iter;
  }
}

/**********************************************************************
 * OpenGL helper functions
 *********************************************************************/

/* Create VBO, IBO and VAO objects for the heightmap geometry and bind them to
 * the specified program object
 */
static void make_mesh(GLuint program) {
  GLuint attrloc;

  glGenVertexArrays(1, &mesh);
  glGenBuffers(4, mesh_vbo);
  glBindVertexArray(mesh);
  /* Prepare the data for drawing through a buffer inidices */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_vbo[3]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * MAP_NUM_LINES * 2, map_line_indices,
               GL_STATIC_DRAW);

  /* Prepare the attributes for rendering */
  attrloc = glGetAttribLocation(program, "x");
  glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[0][0],
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(attrloc);
  glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);

  attrloc = glGetAttribLocation(program, "z");
  glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[2][0],
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(attrloc);
  glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);

  attrloc = glGetAttribLocation(program, "y");
  glBindBuffer(GL_ARRAY_BUFFER, mesh_vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES, &map_vertices[1][0],
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(attrloc);
  glVertexAttribPointer(attrloc, 1, GL_FLOAT, GL_FALSE, 0, 0);
}

/* Update VBO vertices from source data
 */
static void update_mesh(void) {
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * MAP_NUM_TOTAL_VERTICES,
                  &map_vertices[1][0]);
}

/**********************************************************************
 * GLFW callback functions
 *********************************************************************/

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error #%d: %s\n", error, description);
}

int main(int, char **) {
  try {
    vkfw::setErrorCallback(error_callback);
    auto instance = vkfw::initUnique();

    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    hints.resizable = false;
    hints.contextVersionMajor = 3u;
    hints.contextVersionMinor = 2u;
    hints.openGLProfile = vkfw::OpenGLProfile::eCore;
    hints.openGLForwardCompatibility = true;
    auto window = vkfw::createWindowUnique(800, 600, "GLFW OpenGL3 Heightmap demo", hints);

    /* Register events callback */
    window->callbacks()->on_key = [](vkfw::Window const &window, vkfw::Key key, int,
                                     vkfw::KeyAction action, vkfw::ModifierKeyFlags) {
      if (key == vkfw::Key::eEscape && action == vkfw::KeyAction::ePress)
        window.setShouldClose(true);
    };

    window->makeContextCurrent();
    gladLoadGL((GLADloadfunc) &vkfw::getProcAddress);

    /* Prepare opengl resources for rendering */
    GLuint shader_program = make_shader_program(vertex_shader_text, fragment_shader_text);
    if (shader_program == 0u)
      return -2;

    glUseProgram(shader_program);
    GLint uloc_project = glGetUniformLocation(shader_program, "project");
    GLint uloc_modelview = glGetUniformLocation(shader_program, "modelview");

    /* Compute the projection matrix */
    float f = 1.0f / tanf(view_angle / 2.0f);
    projection_matrix[0] = f / aspect_ratio;
    projection_matrix[5] = f;
    projection_matrix[10] = (z_far + z_near) / (z_near - z_far);
    projection_matrix[11] = -1.0f;
    projection_matrix[14] = 2.0f * (z_far * z_near) / (z_near - z_far);
    glUniformMatrix4fv(uloc_project, 1, GL_FALSE, projection_matrix);

    /* Set the camera position */
    modelview_matrix[12] = -5.0f;
    modelview_matrix[13] = -5.0f;
    modelview_matrix[14] = -20.0f;
    glUniformMatrix4fv(uloc_modelview, 1, GL_FALSE, modelview_matrix);

    /* Create mesh data */
    init_map();
    make_mesh(shader_program);

    /* Create vao + vbo to store the mesh */
    /* Create the vbo to store all the information for the grid and the height */

    /* setup the scene ready for rendering */
    glViewport(0, 0, (GLsizei) window->getFramebufferWidth(),
               (GLsizei) window->getFramebufferHeight());
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* main loop */
    int frame = 0;
    int iter = 0;
    double last_update_time = vkfw::getTime();

    while (!window->shouldClose()) {
      ++frame;
      /* render the next frame */
      glClear(GL_COLOR_BUFFER_BIT);
      glDrawElements(GL_LINES, 2 * MAP_NUM_LINES, GL_UNSIGNED_INT, 0);

      /* display and process events through callbacks */
      window->swapBuffers();
      vkfw::pollEvents();
      /* Check the frame rate and update the heightmap if needed */
      double dt = vkfw::getTime();
      if ((dt - last_update_time) > 0.2) {
        /* generate the next iteration of the heightmap */
        if (iter < MAX_ITER) {
          update_map(NUM_ITER_AT_A_TIME);
          update_mesh();
          iter += NUM_ITER_AT_A_TIME;
        }
        last_update_time = dt;
        frame = 0;
      }
    }
  } catch (std::system_error &err) {
    char error_message[] = "An error has occured: ";
    strcat(error_message, err.what());
    fprintf(stderr, error_message);
    return -1;
  }

  return EXIT_SUCCESS;
}
