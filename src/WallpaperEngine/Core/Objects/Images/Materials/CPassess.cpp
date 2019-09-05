#include "CPassess.h"

using namespace WallpaperEngine::Core::Objects::Images::Materials;

CPassess::CPassess (std::string blending, std::string cullmode, std::string depthtest, std::string depthwrite, std::string shader) :
    m_blending (std::move(blending)),
    m_cullmode (std::move(cullmode)),
    m_depthtest (std::move(depthtest)),
    m_depthwrite (std::move(depthwrite)),
    m_shader (std::move(shader))
{
}

std::vector<std::string>* CPassess::getTextures ()
{
    return &this->m_textures;
}

CPassess* CPassess::fromJSON (json data)
{
    json::const_iterator blending_it = data.find ("blending");
    json::const_iterator cullmode_it = data.find ("cullmode");
    json::const_iterator depthtest_it = data.find ("depthtest");
    json::const_iterator depthwrite_it = data.find ("depthwrite");
    json::const_iterator shader_it = data.find ("shader");
    json::const_iterator textures_it = data.find ("textures");

    if (blending_it == data.end ())
    {
        throw std::runtime_error ("Material pass must have blending specified");
    }

    if (cullmode_it == data.end ())
    {
        throw std::runtime_error ("Material pass must have cullmode specified");
    }

    if (depthtest_it == data.end ())
    {
        throw std::runtime_error ("Material pass must have depthtest specified");
    }

    if (depthwrite_it == data.end ())
    {
        throw std::runtime_error ("Material pass must have depthwrite specified");
    }

    if (shader_it == data.end ())
    {
        throw std::runtime_error ("Material pass must have shader specified");
    }

    if (textures_it != data.end ())
    {
        if ((*textures_it).is_array () == false)
        {
            throw std::runtime_error ("Textures for material must be a list");
        }
    }

    CPassess* pass = new CPassess (
        *blending_it,
        *cullmode_it,
        *depthtest_it,
        *depthwrite_it,
        *shader_it
    );

    if (textures_it != data.end ())
    {
        json::const_iterator cur = (*textures_it).begin ();
        json::const_iterator end = (*textures_it).end ();

        for (;cur != end; cur ++)
        {
            if ((*cur).is_null () == true)
            {
                pass->insertTexture ("");
            }
            else
            {
                pass->insertTexture (*cur);
            }
        }
    }

    return pass;
}


void CPassess::insertTexture (const std::string& texture)
{
    this->m_textures.push_back (texture);
}