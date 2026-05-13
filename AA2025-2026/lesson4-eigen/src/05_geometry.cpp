#include "eigen_fmt_lesson.h"

void demo_geometry() {
    print_subtitle("Geometric Transformations");
    
    // Quaternions
    fmt::print(fg(fmt::color::green), "\n  Quaternions\n");
    double angle = M_PI / 3;
    Vector3d axis(0, 0, 1);
    Eigen::AngleAxisd rot_aa(angle, axis);
    Eigen::Quaterniond q(rot_aa);
    
    fmt::print("    Rotation {}° around Z\n", angle * 180.0 / M_PI);
    fmt::print("    q = (w={:.4f}, x={:.4f}, y={:.4f}, z={:.4f})\n", q.w(), q.x(), q.y(), q.z());
    
    Vector3d v(1, 0, 0);
    Vector3d vr = q * v;
    fmt::print("    v = {}\n", fmt::join(v, ", "));
    fmt::print("    q*v = {}\n", fmt::join(vr, ", "));
    
    // SLERP
    Eigen::Quaterniond q1 = Eigen::Quaterniond::Identity();
    Eigen::Quaterniond q2(Eigen::AngleAxisd(M_PI/2, Vector3d(0,0,1)));
    fmt::print("\n    SLERP:\n");
    for (double t = 0; t <= 1.0; t += 0.25) {
        Eigen::Quaterniond qi = q1.slerp(t, q2);
        fmt::print("      t={:.2f}: ({:.3f}, {:.3f}, {:.3f}, {:.3f})\n", t, qi.w(), qi.x(), qi.y(), qi.z());
    }
    
    // Rotation matrices
    fmt::print(fg(fmt::color::green), "\n  Rotation Matrices\n");
    double th = M_PI / 4;
    Matrix3d Rz;
    Rz << cos(th), -sin(th), 0, sin(th), cos(th), 0, 0, 0, 1;
    fmt::print("    Rz(45°):\n"); PRINT_MAT(Rz); fmt::print("\n");
    fmt::print("    det(Rz) = {:.6f}\n", Rz.determinant());
    fmt::print("    Rz * Rzᵀ = I:\n"); PRINT_MAT(Rz * Rz.transpose()); fmt::print("\n");
    
    // 4x4 Transform
    fmt::print(fg(fmt::color::green), "\n  3D Transform (4x4)\n");
    Matrix4d T = Matrix4d::Identity();
    T.block<3,3>(0,0) = Rz;
    T.block<3,1>(0,3) = Vector3d(1, 2, 3);
    
    fmt::print("    T:\n"); PRINT_MAT(T); fmt::print("\n");
    
    Vector4d ph(1, 0, 0, 1);
    Vector4d pt = T * ph;
    fmt::print("    Point (1,0,0) -> ({:.2f}, {:.2f}, {:.2f})\n", pt(0), pt(1), pt(2));
    
    // Perspective projection
    fmt::print(fg(fmt::color::green), "\n  Perspective Projection\n");
    double fov = M_PI / 4, aspect = 16.0/9.0, near = 0.1, far = 100.0;
    double f = 1.0 / tan(fov/2);
    
    Matrix4d proj = Matrix4d::Zero();
    proj(0,0) = f/aspect; proj(1,1) = f;
    proj(2,2) = (far+near)/(near-far); proj(2,3) = 2*far*near/(near-far);
    proj(3,2) = -1;
    
    for (double z : {-1.0, -5.0, -20.0}) {
        Vector4d p3(0.5, 0.3, z, 1);
        Vector4d p2 = proj * p3;
        p2 /= p2(3);
        fmt::print("    3D({:.1f}, {:.1f}, {:.1f}) -> 2D({:.3f}, {:.3f})\n",
                   p3(0), p3(1), p3(2), p2(0), p2(1));
    }
}
