#pragma once

class Graphics
{
public:
   static Graphics* Get();

protected:
   static Graphics* m_singleton;
   Graphics();
   ~Graphics();
};

