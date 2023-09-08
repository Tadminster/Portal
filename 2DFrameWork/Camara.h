#pragma once
class Camera : public Actor
{

private:
    static ID3D11Buffer* VPBuffer;


public:
    Matrix              view, proj, VP;     
    Viewport            viewport;  
    bool		        ortho;
    float		        fov, nearZ, farZ, width, height;
    static Camera* main;
    static float mainCamSpeed;
public:
    static void CreateStaticMember();
    static void DeleteStaticMember();
    static void ControlMainCam();
    static Camera* Create(string name = "Camera");
protected:
    Camera();
    ~Camera();
public:
    void	        Update() override;
    void            Set();
    void            ResizeScreen();
    void	        RenderDetail();
};