//
// Created by Julia on 2019-06-10.
//

#ifndef OPENGLSETUP_MATERIALLOADER_H
#define OPENGLSETUP_MATERIALLOADER_H

#include <memory>
class Material;

class MaterialLoader {
public:
    std::shared_ptr<Material> load(const std::string &Path);
};


#endif //OPENGLSETUP_MATERIALLOADER_H
