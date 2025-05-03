import unittest

from n64img.image import (
    Image,
    CI4,
    CI8,
    I1,
    I4,
    I8,
    IA4,
    IA8,
    IA16,
    RGBA16,
    RGBA32,
)


class TestImage(unittest.TestCase):
    def test_size(self):
        img = Image(bytes(), 32, 32)
        self.assertEqual(1024, img.size())

    def test_mipmap_size(self):
        img = Image(bytes(), 32, 32)
        # 4x4 needs 4 pixels extra per row; (4+4)*1 = 8
        # 2x2 needs 6 pixels extra per row; (2+6)*1 = 8
        # 1x1 needs 7 pixels extra per row; (1+7)*1 = 8
        # 32*32*1 + 16*16*1 + 8*8*1 + 8*4*1 + 8*2*1 + 8*1*1
        self.assertEqual(1400, img.mipmap_size())


class TestCI4(unittest.TestCase):
    def test_size(self):
        img = CI4(bytes(), 32, 32)
        self.assertEqual(512, img.size())


class TestCI8(unittest.TestCase):
    def test_size(self):
        img = CI8(bytes(), 32, 32)
        self.assertEqual(1024, img.size())


class TestI1(unittest.TestCase):
    def test_size(self):
        img = I1(bytes(), 32, 32)
        self.assertEqual(128, img.size())


class TestI4(unittest.TestCase):
    def test_size(self):
        img = I4(bytes(), 32, 32)
        self.assertEqual(512, img.size())


class TestI8(unittest.TestCase):
    def test_size(self):
        img = I8(bytes(), 32, 32)
        self.assertEqual(1024, img.size())


class TestIA4(unittest.TestCase):
    def test_size(self):
        img = IA4(bytes(), 32, 32)
        self.assertEqual(512, img.size())


class TestIA8(unittest.TestCase):
    def test_size(self):
        img = IA8(bytes(), 32, 32)
        self.assertEqual(1024, img.size())


class TestIA16(unittest.TestCase):
    def test_size(self):
        img = IA16(bytes(), 32, 32)
        self.assertEqual(2048, img.size())


class TestRGBA16(unittest.TestCase):
    def test_size(self):
        img = RGBA16(bytes(), 32, 32)
        self.assertEqual(2048, img.size())

    def test_mipmap_size(self):
        img = RGBA16(bytes(), 32, 32)
        # 2x2 needs 2 pixels extra per row; (2+2)*2 = 8
        # 1x1 needs 3 pixels extra per row; (1+3)*2 = 8
        # 32*32*2 + 16*16*2 + 8*8*2 + 4*4*2 + 4*2*2 + 4*1*2
        self.assertEqual(2744, img.mipmap_size())


class TestRGBA32(unittest.TestCase):
    def test_size(self):
        img = RGBA32(bytes(), 32, 32)
        self.assertEqual(4096, img.size())

    def test_mipmap_size(self):
        img = RGBA32(bytes(), 32, 32)
        # 1x1 needs 1 pixels extra per row; (1+1)*4 = 8
        # 32*32*4 + 16*16*4 + 8*8*4 + 4*4*4 + 2*2*4 + 2*1*4
        self.assertEqual(5464, img.mipmap_size())

    def test_mipmap_size2(self):
        # TODO: sanity check this
        img = RGBA32(bytes(), 31, 31)
        # 31x31 needs 1 pixel extra per row; (31+1)*4 = 128
        # 15x15 needs 1 pixel extra per row; (15+1)*4 = 64
        # 7x7 needs 1 pixel extra per row; (7+1)*4 = 32
        # 3x3 needs 1 pixel extra per row; (3+1)*4 = 16
        # 1x1 needs 1 pixel extra per row; (1+1)*4 = 8
        # 32*31*4 + 16*15*4 + 8*7*4 + 4*3*4 + 2*1*4
        self.assertEqual(5208, img.mipmap_size())
