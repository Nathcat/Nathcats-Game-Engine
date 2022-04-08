#define MATERIAL_H

#ifndef FRAMEWORK_H
#include "framework.h"
#endif

#ifndef SHADER_H
#include "Shader.h"
#endif

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

// Not all of the possible formats for input layout entries
// are currently available.
#define SHADERINPUT_R32G32B32_FLOAT DXGI_FORMAT_R32G32B32_FLOAT
#define SHADERINPUT_R32G32B32A32_FLOAT DXGI_FORMAT_R32G32B32A32_FLOAT

/// <summary>
/// Material class, this will be attached to a MeshRenderer to define how 
/// a mesh should appear.
/// </summary>
class Material {
public:
	Shader* pShader;
	char** elementsArray;

	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="_pShader"></param>
	Material(Shader* _pShader) {
		pShader = _pShader;
		elementsArray = new char* [pShader->numberOfElements];
	}

	/// <summary>
	/// Assign a value to an element which will be passed to the shader program.
	/// </summary>
	/// <typeparam name="ElementType">The type of the element</typeparam>
	/// <param name="semanticName">The semantic name that the value is being passed to</param>
	/// <param name="element">The element itself</param>
	template<class ElementType> void AssignValueToElement(LPCWSTR semanticName, UINT semanticIndex, ElementType element) {
		int index = NULL;

		for (int i = 0; i < pShader->numberOfElements; i++) {
			if ((pShader->pInputLayoutDesc + i)->SemanticName == semanticName && (pShader->pInputLayoutDesc + i)->SemanticIndex == semanticIndex) {
				index = i;
			}
		}

		if (index != NULL) {
			*(elementsArray + index) = (char*)&element;
		}
		else {
			throw NoSuchElementException()
		}
	}

	/// <summary>
	/// Get the value of an element.
	/// </summary>
	/// <typeparam name="ElementType">The type of the element</typeparam>
	/// <param name="semanticName">The semantic name the element is to be passed to</param>
	/// <param name="semanticIndex">The semantic index the element is to be passed to</param>
	/// <returns>A pointer to the value</returns>
	template<class ElementType> ElementType* GetElementValue(LPCWSTR semanticName, UINT semanticIndex) {
		int index = NULL;

		for (int i = 0; i < pShader->numberOfElements; i++) {
			if ((pShader->pInputLayoutDesc + i)->SemanticName == semanticName && (pShader->pInputLayoutDesc + i)->SemanticIndex == semanticIndex) {
				index = i;
			}
		}

		return (ElementType*)*(elementsArray + index);
	}

	/// <summary>
	/// Get the size of the elements array.
	/// </summary>
	/// <returns>std::size_t type, the size of the elements array.</returns>
	std::size_t GetSizeOfElementsArray() {
		std::size_t result;
		
		for (int i = 0; i < pShader->numberOfElements; i++) {
			if ((pShader->pInputLayoutDesc + i)->Format == SHADERINPUT_R32G32B32_FLOAT) {
				result += (std::size_t) 12;
			}
			else if ((pShader->pInputLayoutDesc + i)->Format == SHADERINPUT_R32G32B32A32_FLOAT) {
				result += (std::size_t) 16;
			}
		}

		return result;
	}
};
