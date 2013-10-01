#include "shader.h"

Shader::Shader(string shaderName) : name(shaderName) {}

void Shader::Init() {
	program = glCreateProgram();
	
	string fragName = name + string(FRAG_EXT);
	string vertName = name + string(VERT_EXT);

	vertex = CreateShader(GL_VERTEX_SHADER, vertName);
	fragment = CreateShader(GL_FRAGMENT_SHADER, fragName);

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	// must be done before linking
	SetDefaultAttributes();

	Link();
}

Shader::~Shader(void) {
	glDetachShader(program, fragment);
	glDeleteShader(fragment);

	glDetachShader(program, vertex);
	glDeleteShader(vertex);

	glDeleteProgram(program);
}

string Shader::GetName() const {
	return name;
}

GLuint Shader::Program() {
	return program;
}

bool Shader::Link() {
	glLinkProgram(program);

	GLint code;
	glGetProgramiv(program, GL_LINK_STATUS, &code);

	return code == GL_TRUE ? true : false ;
}

void Shader::SetDefaultAttributes() {
	glBindAttribLocation(program, VERTEX_BUFFER, "position");
	glBindAttribLocation(program, TEXTURE_BUFFER, "uv");
	glBindAttribLocation(program, COLOUR_BUFFER, "colour");
}

bool Shader::LoadShaderSource(string& path, string& into) {
	ifstream file;
	string buffer;

	cout << path << " :" << endl;
	
	file.open(path.c_str());

	if(!file.is_open()) {
		cout << "Opening file failure" << endl;
		return false;
	}

	while(!file.eof()) {
		getline(file, buffer);
		into += buffer + "\n";
	}

	file.close();
	//cout << into << endl << endl;
	cout << "Shader source loaded" << endl;

	return true;
}

GLuint Shader::CreateShader(GLenum type, string& file) {
	string path = string(RELATIVE_PATH) + file;	
	string source;

	if(!LoadShaderSource(path, source)) {
		cout << "Creation of shader failed" << endl;
		return 0;
	}

	GLuint shader = glCreateShader(type);

	const GLchar* chars = source.c_str();

	glShaderSource(shader, 1, &chars, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status != GL_TRUE) {
		char error[512];

		glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		cout << "Impossible de compiler le shader" << endl;
		cout << file << " : " << error;

		return 0;
	} 

	cout << "Shader compilation successfull" << endl;

	return shader;
}


